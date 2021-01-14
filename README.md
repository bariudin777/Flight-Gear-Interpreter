# Flight-Gear-Interpreter

"Flight-Gear: Interpreter"- First Mile-Stone:

    •	 Establishing Tcp/Ip connection with the simulator.
  
    •	 Writing commands for the plane flight.
  
General:
  1.	We use “Flight-Gear” installation ( Flight-Gear site- https://www.flightgear.org/download/).
  2.	The invitumant is - Linux.
  3.	Tcp protocol- “Generic Small” is needed( you need to add it to /data/Protocol directory.


Notes:

1.Specification of tcp/ip and other protocol is needed.Here is what you need to fill:

        --telnet=socket,in,10,127.0.0.1,5402,tcp
        
        --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
        
And this is where:

![](flight-gear%20manu.png)
