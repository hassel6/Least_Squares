#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector< vector<double> > MatrixA( vector <double> x0, int cnt ) {
    vector<double> sums( 5, 0.0 );
    vector<vector<double> > outputMatrix( 3, vector<double>( 3, 0.0 ) );
    static int i{ 0 }, j{ 0 }, k{ 0 };

    while( j < 5 ) {
        for( i = 0; i < int(x0.size()); i++ ) {
            switch( j ) {
                case 0: {
                    sums[ j ] = cnt;
                    break;
                }
                case 1: {
                    sums[ j ] = sums[ j ] + x0[ i ];
                    break;
                }
                case 2: {
                    sums[ j ] = sums[ j ] + pow( x0[ i ], 2 );
                    break;
                }
                case 3: {
                    sums[ j ] = sums[ j ] + pow( x0[ i ], 3 );
                    break;
                }
                case 4: {
                    sums[ j ] = sums[ j ] + pow( x0[ i ], 4 );
                    break;
                }
            }
        }
        j++;
    }

    for( i = 0; i < 3; i++ ) {
        for( j = 0; j < 3; j++ ) {
            outputMatrix[ i ][ j ] = sums[ k++ ];
        }
        k -= 2;
    }
    return outputMatrix;
}

vector<double> MatrixB( vector < double > x0, vector < double > y0 ) {
    vector<double> sums(3, 0.0);
    vector<double> outputMatrix(3, 0.0);
    static int i = 0, j = 0;

    while( j < 3 ) {
        for( i = 0; i < int(y0.size()); i++ ) {
            switch( j ) {
                case 0: {
                    sums[ j ] = sums[ j ] + y0[ i ];
                    break;
                }
                case 1: {
                    sums[ j ] = sums[ j ] + ( x0[ i ] * y0[ i ] );
                    break;
                }
                case 2: {
                    sums[ j ] = sums[ j ] + ( pow( x0[ i ], 2 ) * y0[ i ] );
                    break;
                }
            }
        }
        j++;
    }

    for( i = 0; i < 3; i++ ) {
        outputMatrix[ i ] = sums[ i ];
    }
    return outputMatrix;
}

double determinantOfMinor( int theRowHeightY, int theColumnWidthX, vector< vector<double> > outputMatrix )
{
  int x1 = theColumnWidthX == 0 ? 1 : 0;
  int x2 = theColumnWidthX == 2 ? 1 : 2;
  int y1 = theRowHeightY   == 0 ? 1 : 0;
  int y2 = theRowHeightY   == 2 ? 1 : 2;

  return ( outputMatrix[ y1 ][ x1 ] * outputMatrix[ y2 ][ x2 ] )
      -  ( outputMatrix[ y1 ][ x2 ] * outputMatrix[ y2 ][ x1 ] );
}

double determ( vector< vector<double> > MatA ) {
    return (
    MatA[0][0] * ( ( MatA[1][1] * MatA[2][2]) - (MatA[1][2] * MatA[2][1] ) )
    - MatA[0][1] * ( ( MatA[1][0] * MatA[2][2] )
    -( MatA[1][2] * MatA[2][0] ) ) + MatA[0][2]
    * ( ( MatA[1][0] * MatA[2][1] - MatA[1][1] * MatA[2][0] ) )
    );
}

vector< vector<double> > inverse( vector< vector<double> > theMatrix ) {
    vector< vector<double> > outputMatrix( 3, vector<double>( 3, 0.0 ) );
    static double oneOverDeterminant = 1.0 / determ( theMatrix );

    for ( int y = 0;  y < 3;  y ++ ) {
        for ( int x = 0;  x < 3;  x ++ ) {
            outputMatrix[ y ][ x ] = determinantOfMinor( x, y, theMatrix ) * oneOverDeterminant;

            if( 1 == ( ( x + y ) % 2 ) ) {
                outputMatrix[ y ][ x ] =- outputMatrix[ y ][ x ];
            }
        }
    }
    return outputMatrix;
}

///////////////////////////////////// PRINT ////////////////////////////////////////////

void print2DVector( vector< vector<double> >, const string );
void printVector( vector<double>, const string );

///////////////////////////////////////////////////////////////////////////////////////////

int main() {

    /////////DATA
    vector< vector<double> > MatA(3, vector<double> ( 3, 0.0 ) );
    vector<double> MatB(3, 0.0);
    vector<double> alphaValues( 3, 0.0 );

    vector<double> xValues;
    vector<double> yValues;

    auto dValue{ 0.0 };
    int dCoefCount{0};
    int c{0};
    //////////////////////

    ////////INFO AND INPUTS
    cout << "#################################" << endl;
    cout << "##### Least Squares Method ######" << endl;
    cout << "#################################\n\n" << endl;

    cout << "Input : X and Y Values Count";
    cin >> dCoefCount;
    cout << "-----------------------------------\n" << endl;

    cout << "=>You can give input like: x1 x2 x3 ... xn" << endl;
    cout << "=>Input X Values:  ";

    while ( c < dCoefCount ) {

        cin >> dValue;
        xValues.push_back( dValue );
        c++;
    }

    dValue = 0.0;
    c = 0;
    cout << "\n-----------------------------------" << endl;
    cout << "=>You can give input like: y1 y2 y3 ... yn" << endl;
    cout << "=>Input Y Values:";

    while ( c < dCoefCount ) {
        cin >> dValue;
        yValues.push_back( dValue );
        c++;
    }
    /////////////////////////

    ////////////PRINT ALL
    MatA = MatrixA( xValues, dCoefCount );
    MatB = MatrixB( xValues, yValues );
    //
    printVector( xValues, "X Values=" );
    printVector( yValues, "Y Values=" );
    //
    print2DVector( MatA, "A Matrix=" );
    printVector( MatB, "Y Matrix=" );
    //
    MatA = inverse( MatA );

        for( int i = 0; i < 3; i++ )
            for( int j = 0; j < 3; j++ ) alphaValues[ i ] = alphaValues[ i ] + ( MatA[ i ][ j ] * MatB[ j ] );

    printVector( alphaValues, "Alpha Values=" );
    //////////////////////////////////////
    cin >> dCoefCount;
    return 0;
}

void print2DVector( vector < vector < double > > outputMatrix, const string szTitle ) {
    static unsigned int i{ 0 };
    static unsigned int j{ 0 };

    cout << "\n-----------------------------------" << endl;
    cout << szTitle << endl;
    for( i = 0; i < outputMatrix.size(); i++ ) {
        cout << "|";
        for( j = 0; j < outputMatrix[ i ].size(); j++ ) {
            if( j == ( outputMatrix[ i ].size() - 1 ) ) cout << outputMatrix[ i ][ j ];
            else                                        cout << outputMatrix[ i ][ j ] << " ";
        }
    cout << "|" << endl;
    }
    cout << "-----------------------------------" << endl;
}

void printVector( vector < double > outputMatrix, const string szTitle ) {
    static unsigned int i{ 0 };
    cout << "\n\n-----------------------------------------------------" << endl;
    cout << szTitle << " [";
    for( i = 0; i < outputMatrix.size(); i++ ) {
            if( i == ( outputMatrix.size() - 1 ) ) cout << outputMatrix[ i ];
            else                          cout << outputMatrix[ i ] << " ";

    }
    cout << "]";
    cout << "\n-----------------------------------------------------" << endl;
}