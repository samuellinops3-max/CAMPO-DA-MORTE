static void read_pad(void)
{
    padInfo info;
    padData d;
    pad_ax = pad_ay = pad_mag = 0.0f;
    pad_boost = pad_x = pad_start = 0;
    pad_connected = 0;

    ioPadGetInfo(&info);
    for (int p = 0; p < 7; p++) {
        if (info.status[p]) {
            memset(&d, 0, sizeof(d));
            if (ioPadGetData(p, &d) == 0) {
                pad_connected = 1;
                
                // Leitura do Analógico Esquerdo
                float ax = ((int)d.ANA_L_H - 128) / 128.0f;
                float ay = ((int)d.ANA_L_V - 128) / 128.0f;
                if (fabsf(ax) < 0.15f) ax = 0.0f;
                if (fabsf(ay) < 0.15f) ay = 0.0f;

                // Leitura das Setinhas (D-PAD) como alternativa
                float dx = 0.0f, dy = 0.0f;
                if (d.BTN_LEFT)  dx -= 1.0f;
                if (d.BTN_RIGHT) dx += 1.0f;
                if (d.BTN_UP)    dy -= 1.0f;
                if (d.BTN_DOWN)  dy += 1.0f;
                
                if (dx != 0.0f || dy != 0.0f) { 
                    ax = dx; 
                    ay = dy; 
                }

                pad_ax = ax; 
                pad_ay = ay;
                pad_mag = sqrtf(ax * ax + ay * ay);
                if (pad_mag > 1.0f) pad_mag = 1.0f;

                pad_boost = (d.BTN_CROSS || d.BTN_R1 || d.BTN_R2) ? 1 : 0;
                pad_x = d.BTN_CROSS ? 1 : 0;
                pad_start = d.BTN_START ? 1 : 0;
                break;
            }
        }
    }
}
