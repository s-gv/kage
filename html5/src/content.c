// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content.h"

Sprite g_start_splash_sprite = {
    (0000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (1023.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
    4.0f, 2.0f,
};

Sprite g_stop_splash_sprite = {
    (0000.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
    (1023.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
    4.0f, 2.0f,
};

Sprite g_farbg_sprites[2] = {
    {
        (0000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        4.0f, 2.0f
    },
    {
        (0000.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        4.0f, 2.0f
    }
};

Sprite g_kage_sprites[8] = {
    {
        (000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (128.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (384.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (639.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (640.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (895.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (896.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    }
};

Sprite g_kage_dying_sprites[8] = {
    {
        (000.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (128.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (384.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (639.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (640.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    }
};

Sprite g_crap_sprites[3] = {
    {
        (768.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (895.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (896.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (000.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (383.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    }
};

Sprite g_target_sprites[24] = {
    {
        (000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (000.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },



    {
        (000.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (000.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (128.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (128.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (384.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (384.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (639.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (639.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (640.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (640.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (895.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (895.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (896.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (896.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
};

Sprite g_cloud_sprites[4] = {
    {
        (000.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.8f, 0.4f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.8f, 0.4f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.8f, 0.4f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.8f, 0.4f,
    }
};

Sprite g_bush_sprites[4] = {
    {
        (000.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    }
};

Sprite g_building_sprites[8] = {
    {
        (000.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (000.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (768.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.8f, 0.8f,
    }
};

Sprite g_food_sprites[4] = {
    {
        (256.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (384.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (639.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (640.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    }
};

Sprite g_pause[1] = {
    {
        (128.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (383.0f + 0.5f)/1024.0f,
        0.15f, 0.15f,
    }
};

Sprite g_play[1] = {
    {
        (256.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (383.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    }
};

Sprite g_darken[1] = {
    {
        (384.0f + 0.5f)/1024.0f, (256.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (383.0f + 0.5f)/1024.0f,
        10.0f, 10.0f,
    }
};

Sprite g_obstacle_sprites[1] = {
    {
        (000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.5f, 0.25f,
    },
};

Sprite g_nums[10] = {
    {
        (000.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (63.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (64.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (128.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (191.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (192.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (319.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (320.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (384.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (447.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (448.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (575.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
    {
        (576.0f + 0.5f)/1024.0f, (384.0f + 0.5f)/1024.0f,
        (639.0f + 0.5f)/1024.0f, (511.0f + 0.5f)/1024.0f,
        0.05f, 0.1f,
    },
};

Sprite g_big_nums[10] = {
    {
        (000.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (63.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (63.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (128.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (191.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (192.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (319.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (320.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (383.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (384.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (447.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (448.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (575.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
    {
        (578.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (639.0f + 0.5f)/1024.0f, (639.0f + 0.5f)/1024.0f,
        0.125f, 0.25f,
    },
};

Sprite g_roads[1] = {
    {
        (0.000f + 0.5f)/1024.0f, (640.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        4.0f, 0.5f,
    },
};

AnimSeq g_kage_anim = {
    {
        {&g_kage_sprites[0], 2},
        {&g_kage_sprites[1], 2},
        {&g_kage_sprites[2], 2},
        {&g_kage_sprites[3], 2},
        {&g_kage_sprites[4], 2},
        {&g_kage_sprites[5], 2},
        {&g_kage_sprites[6], 2},
        {&g_kage_sprites[7], 2},

        {&g_kage_sprites[7], 2},
        {&g_kage_sprites[6], 2},
        {&g_kage_sprites[5], 2},
        {&g_kage_sprites[4], 2},
        {&g_kage_sprites[3], 2},
        {&g_kage_sprites[2], 2},
        {&g_kage_sprites[1], 2},
        {&g_kage_sprites[0], 2},
    },
    16
};

AnimSeq g_kage_dying_anim = {
    {
        {&g_kage_dying_sprites[0], 4},
        {&g_kage_dying_sprites[1], 4},
        {&g_kage_dying_sprites[2], 4},
        {&g_kage_dying_sprites[3], 4},
        {&g_kage_dying_sprites[4], 4},
        {&g_kage_dying_sprites[5], 4},
    },
    6
};