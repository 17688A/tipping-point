#include "./modular.h"

void PneumaticSwitch()
{
	switch(pneumaticStatus)
    {
    	case 0:
    	{
			pneumaticStatus = 1;
			Pneumatic.set(true);
			break;
      	}
      	case 1:
      	{
        	pneumaticStatus = 0;
        	Pneumatic.set(false);
        	break;
      	}
	}
}

void PneumaticSwitchBack()
{
	switch(pneumaticStatusBack)
  	{
  		case 0:
  		{
    		pneumaticStatusBack = 1;
    		PneumaticBack.set(true);
    		break;
  		}
  		case 1:
  		{
    		pneumaticStatusBack = 0;
    		PneumaticBack.set(false);
    		break;
  		}
  	}		
}
