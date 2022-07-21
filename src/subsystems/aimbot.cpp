#include "main.h"


//change to the center of the vision sensor coords
static int CX = 0, CY = 0;



//angler changes with y offset (task)
void fixAnglerOffset(void) {
    while(true) {
        //gets an object given a signature (size, sig) -> 0 is largest
        vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);
        
        double offset = CY - (rtn.top_coord + (double)rtn.height/2);
        //the ideal height is CY, we are an offset away from that height
        
        //rotate angle until offset is 0
        //we're going to have to tune it based on how slow/fast it turns
        double K_a = 1.5;
        angler.move_velocity(offset * K_a);
        Task::delay(1);
    }

}

//turntable changes with x offset (task)
void fixTurntableOffset(void) {
   while(true) {
        //gets an object given a signature (size, sig) -> 0 is largest
        vision_object_s_t rtn = vision_sensor.get_by_sig(0, 1);
        
        double offset = CX - (rtn.left_coord + (double)rtn.width/2);
        //the ideal height is CX, we are an offset away from that height
        
        //rotate angle until offset is 0
        //we're going to have to tune it based on how slow/fast it turns
        double K_t = 1.5;
        turntable.move_velocity(offset * K_t);
        Task::delay(1);
   }
}