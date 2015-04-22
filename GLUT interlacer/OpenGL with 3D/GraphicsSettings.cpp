#include "GraphicsSettings.h"


static GraphicsSettings* _instance;

GraphicsSettings::GraphicsSettings() {};

GraphicsSettings* GraphicsSettings::getSingleton()
{
	if ( !_instance )
	{
		_instance = new GraphicsSettings();
	}
	return _instance;
}
