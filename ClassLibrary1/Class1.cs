using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using InTheHand.Net.Sockets;
using InTheHand.Net;
using InTheHand.Net.Bluetooth;
using InTheHand.Windows.Forms;
using System.Net.Sockets;
using System.Diagnostics;
using System.Threading;


namespace headbandController
{
    //this is the class that will deal with certain inputs and how to deal with those inputs 
    public class Movement
    {
        //this will be the read in value 
        private float currentData;

        //getter (may not need this) 
        public float getData() { return currentData; }

        //setter
        public void setData(float curr) { currentData = curr; }

        //this is the function that recieves the data, and then returns a uniform output to Unity
        //in Unity we can take this uniform output and use the movement capabilities from there
        public int getMovement()
        {
            //if the float input recieved is within this range, then move FORWARDS
            if (currentData > 0 && currentData <= 1) { return 1; }

            //if the float input recieved is within this range, then move BACKWARDS
            if (currentData > 1 && currentData <= 2) { return 2; }

            //if the float input recieved is within this range, then move RIGHT
            if (currentData > 2 && currentData <= 3) { return 3; }

            //if the float input recieved is within this range, then move
            if (currentData > 3 && currentData <= 4) { return 4; }

        }
    }
}
