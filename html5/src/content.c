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

Sprite g_crap_sprites[2] = {
    {
        (000.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (127.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (128.0f + 0.5f)/1024.0f, (128.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (255.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    }
};

Sprite g_target_sprites[8] = {
    {
        (000.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (000.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (256.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        (511.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (512.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        (767.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
    },
    {
        (768.0f + 0.5f)/1024.0f, (767.0f + 0.5f)/1024.0f,
        (1023.0f + 0.5f)/1024.0f, (1023.0f + 0.5f)/1024.0f,
        0.25f, 0.25f,
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

Sprite g_obstacle_sprites[1] = {
    {
        (000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
        (255.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
        0.5f, 0.25f,
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