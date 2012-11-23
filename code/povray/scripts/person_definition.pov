#declare shirt_texture_scale = 0.1;

#declare left_knee = 0;
#declare right_knee = 0;

#declare left_hip = 0;
#declare right_hip = 0;

#declare left_elbo = 45; // between 0 and 120
#declare right_elbo = 15; // between 0 and 120

#declare left_shoulder_pitch = 50; // between 120 and -90
#declare right_shoulder_pitch = 80;

#declare left_shoulder_roll = -60;  // affects the lower arm.
#declare right_shoulder_roll = -10;   // between 0 and -140

#declare left_shoulder_yaw = -30;   // btween -120 and 10.
#declare right_shoulder_yaw = -10;

#declare left_wrist = 0;
#declare right_wrist = 0;

#declare yaw = 0;

#declare head_yaw = 0;
#declare head_pitch = 0;

#declare tallness = 1;
#declare fatness = 1;

#declare skin_texture = texture {
  pigment {
    color rgb < 203, 110, 75> / 255
  }
  finish {
    ambient 0.3
  }
}

background {
  color rgb <0, 0, 1>
}

camera {
    perspective
//    location <0,10,-1>
//    location <-10,2,-1>
    location <0,5,-10>
    look_at <0,0,0>
    right 1.33*x
    up y
}

#declare shirt_texture = texture {
  pigment {
    bozo
    color_map{ [0.0 color rgb <0, 0, 0>]
               [0.2 color rgb <1,0,0>]
               [0.5 color rgb <.5,.8,.5>]
               [0.8 color rgb <0,1,1>]
               [1. color rgb <1,1,1>]
             }
//    color rgb <0, 0.8, .6>
    scale shirt_texture_scale * 2
//    color rgb <1, 0, 0>
  }
  normal {
//    agate 0.7
//    scale 1.
//    bozo 0.7
    bumps 0.6
    scale 0.09
//    crackle 1.
//    agate 0.2
//    scale 0.3
    turbulence 0.4
  }
  finish {
//    specular 0.001
//    crand 0.01
    ambient 0.3
  }
}

global_settings { ambient_light rgb <0.8, 0.8, 0.8> }
light_source {
   <-10, 5, -10>, rgb <0.9, 0.9, 0.9>
}
light_source {
   <3, 4, 20>, rgb <0.9, 0.9, 0.9>
}

#declare smooth_cylinder = union {
  cylinder {
    <0, 0, 0>, <0, 1, 0>, 0.15 * fatness
  }
  sphere {
    <0, 0, 0>, 0.15 * fatness
  }
  sphere {
    <0, 1, 0>, 0.15 * fatness
  }
}

// Left arm.
union {
  object {
    smooth_cylinder
    transform {
      scale <0.85, 1, 0.85>
      rotate <0, 0, 90>
      rotate <0, 0, -left_elbo>
    }
  }
  object {
    smooth_cylinder
    transform {
      scale <1.15, 1, 1.15>
      rotate <0, 0, 90>
      translate <1, 0, 0>
    }
  }
  transform {
    translate <-1, 0, 0>
    rotate <left_shoulder_roll, 0, 0>   // between 0. and -140.
    rotate <0, 0, left_shoulder_pitch>  // between 120 and -90.
    rotate <0, left_shoulder_yaw, 0>    // between -120 and 10.
    translate <-0.5, 1.6, 0>
  }
  texture {
    shirt_texture
  }
}

// Right arm.
union {
  object {
    smooth_cylinder
    transform {
      scale <0.85, 1, 0.85>
      rotate <0, 0, -90>
      rotate <0, 0, right_elbo>
    }
  }
  object {
    smooth_cylinder
    transform {
      scale <1.15, 1, 1.15>
      rotate <0, 0, -90>
      translate <-1, 0, 0>
    }
  }
  transform {
    translate <1, 0, 0>
    rotate <right_shoulder_roll, 0, 0>
    rotate <0, 0, -right_shoulder_pitch> // between 120 and -90
    rotate <0, -right_shoulder_yaw, 0> // between -120 and 10.
    translate <0.5, 1.6, 0>
  }
  texture {
    shirt_texture
  }
} 

// Neck
object {
  smooth_cylinder
  transform {
    scale <1.1, 0.7, 1.1>
    translate <0, 1.7, 0>
  }
  texture {
    skin_texture
  }
}

// Head
sphere {
  <0, 0.5, 0>, 0.5
  texture {
  pigment {
        image_map {
          png "wrap_face.png"
          map_type 2
          once
        }
        transform {
          rotate <0, -90, 0>
        }
  }
  finish {
   ambient 0.4
  }
  }
  transform {
    scale 0.7
    scale <0.8, 1.3, 1.1>
    translate <0, 1.8, -.1>
  }
}

// Torso
union {
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <-0.3, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <-0.25, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <-0.2, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <-0.15, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <-0.1, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <-0.05, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <0.0, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <0.05, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <0.1, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <0.15, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <0.2, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <0.25, 0, 0>
    }
  }
  object {
    smooth_cylinder
    transform {
     scale <1.8, 1.5, 1.4>
     translate <0.3, 0, 0>
    }
  }
  texture {
    shirt_texture
  }
}
/*
sphere {
  <0, 0, 0>, 2
  texture {
    shirt_texture
  }
}
*/