static pthread_once_t g_init = PTHREAD_ONCE_INIT;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static int g_haveTrackballLight = 0;
static struct light_state_t g_notification;
static struct light_state_t g_battery;
static int g_backlight = 255;
static int g_trackball = -1;
static int g_buttons = 0;
static int g_attention = 0;
static int g_haveAmberLed = 0;

char const*const TRACKBALL_FILE
        = "/sys/class/leds/jogball-backlight/brightness";

char const*const RED_LED_FILE
        = "/sys/class/leds/red/brightness";

char const*const GREEN_LED_FILE
        = "/sys/class/leds/green/brightness";

char const*const BLUE_LED_FILE
        = "/sys/class/leds/blue/brightness";

char const*const AMBER_LED_FILE
        = "/sys/class/leds/amber/brightness";

char const*const LCD_FILE
        = "/sys/class/leds/lcd-backlight/brightness";

char const*const RED_FREQ_FILE
        = "/sys/class/leds/red/device/grpfreq";

char const*const RED_PWM_FILE
        = "/sys/class/leds/red/device/grppwm";

char const*const RED_BLINK_FILE
        = "/sys/class/leds/red/device/blink";

char const*const AMBER_BLINK_FILE
        = "/sys/class/leds/amber/blink";

char const*const KEYBOARD_FILE
        = "/sys/class/leds/keyboard-backlight/brightness";

char const*const BUTTON_FILE
        = "/sys/class/leds/button-backlight/brightness";

char const*const CAMERA_FLASH_FILE
        = "/sys/class/leds/flash/brightness";