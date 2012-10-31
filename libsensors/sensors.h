/*
 * Copyright (C) 2010 MEMSIC, Inc.
 * Copyright (C) 2012 DevRenax, Inc.
 *
 * Initial Code:
 *	Robbie Cao
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <linux/ioctl.h>

#define CM3623_IOC_MAGIC	'T'
#define CM3623_CALI_0	_IOR(CM3623_IOC_MAGIC,0, int)
#define CM3623_CALI_20	_IOR(CM3623_IOC_MAGIC,1, int)
#define CM3623_CALI_30	_IOR(CM3623_IOC_MAGIC,2, int)

/*
 * /sys/class/misc/cm3623_ps/ps_wake
 * 	0: disable
 * 	1: enable
 *
 * /sys/class/misc/cm3623_ps/ps_control
 * 	als_u: ALS_UP
 *	als_d: ALS_DOWN
 * 	ps_u: PS_UP
 * 	ps_d: PS_DOWN
 */
char command_ps_wake_enable[] = "echo 1 > /sys/class/misc/cm3623_ps/ps_wake";
char command_ps_wake_disable[] = "echo 0 > /sys/class/misc/cm3623_ps/ps_wake";
char command_ps_control_als_up[] = "echo als_u > /sys/class/misc/cm3623_ps/ps_control";
char command_ps_control_als_down[] = "echo als_d > /sys/class/misc/cm3623_ps/ps_control";
char command_ps_control_ps_up[] = "echo ps_u > /sys/class/misc/cm3623_ps/ps_control";
char command_ps_control_ps_down[] = "echo ps_d > /sys/class/misc/cm3623_ps/ps_control";

#define ECOMPASS_IOM			'e'
#define ECOMPASS_IOC_SET_MODE		_IOW(ECOMPASS_IOM, 0x00, short)
#define ECOMPASS_IOC_SET_DELAY		_IOW(ECOMPASS_IOM, 0x01, short)
#define ECOMPASS_IOC_GET_DELAY		_IOR(ECOMPASS_IOM, 0x02, short)
#define ECOMPASS_IOC_SET_AFLAG		_IOW(ECOMPASS_IOM, 0x10, short)
#define ECOMPASS_IOC_GET_AFLAG		_IOR(ECOMPASS_IOM, 0x11, short)
#define ECOMPASS_IOC_SET_MFLAG		_IOW(ECOMPASS_IOM, 0x12, short)
#define ECOMPASS_IOC_GET_MFLAG		_IOR(ECOMPASS_IOM, 0x13, short)
#define ECOMPASS_IOC_SET_OFLAG		_IOW(ECOMPASS_IOM, 0x14, short)
#define ECOMPASS_IOC_GET_OFLAG		_IOR(ECOMPASS_IOM, 0x15, short)
#define ECOMPASS_IOC_SET_PFLAG		_IOW(ECOMPASS_IOM, 0x16, short)
#define ECOMPASS_IOC_GET_PFLAG		_IOR(ECOMPASS_IOM, 0x17, short)
#define ECOMPASS_IOC_SET_LFLAG		_IOW(ECOMPASS_IOM, 0x18, short)
#define ECOMPASS_IOC_GET_LFLAG		_IOR(ECOMPASS_IOM, 0x19, short)
#define ECOMPASS_IOC_SET_APARMS		_IOW(ECOMPASS_IOM, 0x20, int[4])
#define ECOMPASS_IOC_GET_APARMS		_IOR(ECOMPASS_IOM, 0x21, int[4])
#define ECOMPASS_IOC_SET_MPARMS		_IOW(ECOMPASS_IOM, 0x22, int[4])
#define ECOMPASS_IOC_GET_MPARMS		_IOR(ECOMPASS_IOM, 0x23, int[4])
#define ECOMPASS_IOC_SET_OPARMS_YAW	_IOW(ECOMPASS_IOM, 0x24, int[4])
#define ECOMPASS_IOC_GET_OPARMS_YAW	_IOR(ECOMPASS_IOM, 0x25, int[4])
#define ECOMPASS_IOC_SET_OPARMS_PITCH	_IOW(ECOMPASS_IOM, 0x26, int[4])
#define ECOMPASS_IOC_GET_OPARMS_PITCH	_IOR(ECOMPASS_IOM, 0x27, int[4])
#define ECOMPASS_IOC_SET_OPARMS_ROLL	_IOW(ECOMPASS_IOM, 0x28, int[4])
#define ECOMPASS_IOC_GET_OPARMS_ROLL	_IOR(ECOMPASS_IOM, 0x29, int[4])
#define ECOMPASS_IOC_SET_YPR		_IOW(ECOMPASS_IOM, 0x30, int[12])
#define ECOMPASS_IOC_GET_YPR		_IOW(ECOMPASS_IOM, 0x31, int[16])

#define IOC_GET_GPIO_VALUE		_IOW(ECOMPASS_IOM, 0x32, int[2])

#define ID_A (0)
#define ID_M (1)
#define ID_O (2)
#define ID_T (3)
#define ID_L (4)
#define ID_P (5)
#define ID_GY (6)

#define SENSORS_ACCELERATION (1 << ID_A)
#define SENSORS_MAGNETIC_FIELD (1 << ID_M)
#define SENSORS_ORIENTATION (1 << ID_O)
#define SENSORS_TEMPERATURE (1 << ID_T)
#define SENSORS_LIGHT (1 << ID_L)
#define SENSORS_PROXIMITY (1 << ID_P)
#define SENSORS_GYROSCOPE (1 << ID_GY)

#define EVENT_TYPE_ACCEL_X ABS_X
#define EVENT_TYPE_ACCEL_Y ABS_Y
#define EVENT_TYPE_ACCEL_Z ABS_Z
#define EVENT_TYPE_ACCEL_STATUS ABS_WHEEL

#define EVENT_TYPE_MAGV_X ABS_HAT0X
#define EVENT_TYPE_MAGV_Y ABS_HAT0Y
#define EVENT_TYPE_MAGV_Z ABS_BRAKE
#define EVENT_TYPE_MAGV_STATUS ABS_GAS

#define EVENT_TYPE_ORIENT_YAW ABS_RX
#define EVENT_TYPE_ORIENT_PITCH ABS_RY
#define EVENT_TYPE_ORIENT_ROLL ABS_RZ
#define EVENT_TYPE_ORIENT_STATUS ABS_RUDDER

#define CONVERT_A (GRAVITY_EARTH / 32768.0f)
#ifdef GSENSOR_DIRECT_X
#define CONVERT_A_X (CONVERT_A)
#else
#define CONVERT_A_X (-CONVERT_A)
#endif
#ifdef GSENSOR_DIRECT_Y
#define CONVERT_A_Y (CONVERT_A)
#else
#define CONVERT_A_Y (-CONVERT_A)
#endif
#ifdef GSENSOR_DIRECT_Z
#define CONVERT_A_Z (CONVERT_A)
#else
#define CONVERT_A_Z (-CONVERT_A)
#endif

#define CONVERT_M (100.f / 32768.0f)
#define CONVERT_M_X (CONVERT_M)
#define CONVERT_M_Y (CONVERT_M)
#define CONVERT_M_Z (CONVERT_M)

#define CONVERT_O (360.0f / 65536.0f)
#define CONVERT_O_Y (CONVERT_O)
#define CONVERT_O_P (CONVERT_O)
#define CONVERT_O_R (CONVERT_O)

