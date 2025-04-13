a = arduino('COM5','uno');
x=0;
 val=0;  
 actualval=0;  
 amps=0.0;
 totamps=0.0; 
 avgamps=0.0;
 amphr=0.0;
 watt=0.0;
 energy=0.0; 
current=0; 
voltage=220;
for i = 1:100
 current = readVoltage(a, 'A0');
  val =(5.0*current)
 actualval =val-2.5; 
 amps =actualval*10;
 totamps=totamps+amps;
 avgamps=totamps/60; 
 amphr=(avgamps*60);  
 watt =voltage*amps;    
 energy=(watt*60)/3600;      
    disp(energy);
    x= [x energy];
    plot(x)
    grid;
    pause(1);
end




