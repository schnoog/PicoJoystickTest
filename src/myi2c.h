

uint8_t mcpaddresses[6] = {0x20 , 0x21, 0x22, 0x23 , 0x24, 0x25};
int mcpactive[6] = { 0,0,0,0,0,0 };
uint8_t adsaddresses[4] = { 0x48, 0x49, 0x4a, 0x4b};
int adsactive[4] = { 0, 0, 0, 0};


boolean  IsI2CDeviceAvailable( uint8_t dev){   
        Wire.beginTransmission (dev);
        if (Wire.endTransmission() == 0) {
            return true;
        }
        return false;
}

void setActiveI2C(){
    Wire.begin();
    for (int i = 0 ; i < 6; i++) {
        mcpactive[i] = 0;
        if(IsI2CDeviceAvailable(mcpaddresses[i])) mcpactive[i] = 1;
    }

    for (int i = 0 ; i < 4; i++) {
        adsactive[i] = 0;
        if(IsI2CDeviceAvailable(adsaddresses[i])) adsactive[i] = 1;
    }
}



