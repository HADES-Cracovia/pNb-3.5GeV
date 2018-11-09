#ifndef HHYPDATA
#define HHYPDATA

#include <iostream>

namespace AnalysisParameters
{

  float test[2][2][3] = { { { 1, 2, 3 }, { 4, 5, 6 } } , { { 7, 8, 9 }, { 10, 11, 12 } } };

// dTheta
  double electrontheta[2][5] = { { 136.15, -2.15665e-08, 2.45679e-05, -0.00959746, 2.79982 }, // up to 450 MeV/c
                                 { 715.559, 1.5929e-07, -0.000169798, 0.0634792, -8.11378 }, // up to 400 MeV/c 
								};
								
// sin(theta)*dPhi
  double  electronphi[2][5] = { { -81.0459, -1.66422e-07, 0.000164145, -0.0542692, 7.5298 }, // up to 300 MeV/c
                                {  59.1892, -7.4409e-08, 7.15051e-05, -0.0237626, 3.73979 },  // up to 400 MeV/c
							  };
// dTheta
  double  positrontheta[2][5] = { { 292.46, -2.9847e-09, -2.54969e-06, 0.00295394, 0.569012 }, // up to 400 MeV/c
								  { 96.9618, -1.13998e-07, 0.000106037, -0.0323475, 5.3305 } // up to 300 MeV/c
								};
// sin(theta)*dPhi
  double  positronphi[2][5] = { { 716.5, 6.31583e-08, -8.8112e-05, 0.0428119, -7.65562 }, // up to 500 MeV/c
                                { 424.407, -2.74331e-08, 2.91485e-05, -0.00830912, 0.524543 }, // up to 500 MeV/c
						  	  };
								

   void print() 
   {
      for (int i=0; i<2; ++i)
	  for (int j=0; j<2; ++j)
	  for (int k=0; k<3; ++k)
	  std::cout << "i,j,k " << i<<" "<<j<<" "<<k<<" = " << test[i][j][k] << std::endl;
      double (*ptr)[2][5] = 0;
      for (int m=0; m<4; ++m)
	  { 
          switch (m) 
		  {
		     case 0: ptr = &electrontheta;
			         std::cout << " electrontheta ************************ " << std::endl;
			         break;
			 case 1: ptr = &electronphi;
			         std::cout << " electronphi ************************ " << std::endl;
			         break;
			 case 2: ptr = &positrontheta;
			         std::cout << " positrontheta ************************ " << std::endl;
			         break;
			 case 3: ptr = &positronphi;
			         std::cout << " positronphi ************************ " << std::endl;
			         break;
		  }
	     for (int j=0; j<2; ++j)
		    for (int k=0; k<5; ++k)
			{
			    std::cout << " system: " <<j<< " param: " <<k<< " = " << (*ptr)[j][k] << std::endl;
			}
      }
   
   }

}

#endif // HHYPDATA
