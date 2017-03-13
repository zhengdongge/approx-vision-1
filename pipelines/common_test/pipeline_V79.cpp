#include "PipelineUtil.h"
#include "CameraModel.h"

#include <string>
#include <iostream>

// Pipeline V76
// 
// Test type: 
// Debugging for PipelineUtil
// 
// Stages:
// Remosaic, DemosInterp
//

int main(int argc, char **argv) {

  using namespace std;

  // Inform user of usage method
  if ( argc != 6 )
  {
      printf("usage: \n./convert path/to/in/image out/image/dir\n");
      return -1;
  }

  // Input image (path and name)
  char * in_img_path    = argv[1];

  // Output image (just path)
  char * out_path       = argv[2];

  // camera model parameters
  char * cam_model_path = argv[3];
  int wb_index          = atoi(argv[4]);
  int num_ctrl_pts      = atoi(argv[5]); 

  CameraModel *cam_model = new CameraModel(cam_model_path, wb_index, num_ctrl_pts);

  // Specify stages
  PipelineStageRev rev_stages[]   = { RevScale };
  PipelineStageCV cv_stages[]     = { Remosaic };
  PipelineStageFwd fwd_stages[]   = { DemosInterp, Descale };

  int num_stages[]  = { sizeof(rev_stages) / sizeof(rev_stages[0]), 
                        sizeof(cv_stages)  / sizeof(cv_stages[0]), 
                        sizeof(fwd_stages) / sizeof(fwd_stages[0]) }; 

  // run image pipeline with specified stages
  run_image_pipeline( in_img_path, 
                      out_path, 
                      *cam_model,
                      rev_stages, 
                      cv_stages, 
                      fwd_stages, 
                      num_stages );
}
