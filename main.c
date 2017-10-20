
#include <libusb-1.0/libusb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "camac.h"

#define TGT_DEVICE 0x0
#define TGT_INTFC 0x1
#define TGT_ENDPT 0x2
#define TGT_OTHER 0x3

#define REQ_STAD 0x0
#define REQ_CLASS 0x20
#define REQ_VENDOR 0x40

#define DIR_TO_DEVICE 0x0
#define DIR_FROM_DEVICE 0x80

#define CAM_I 0x04
#define CAM_C 0x02
#define CAM_Z 0x01
#define CAM_Ax4 0x40

#define NoWait 0x0
#define WaitForQ 0x1
#define WaitForL 0x80



int32_t device_control_msg(struct libusb_device_handle *handle, uint8_t req_type, uint8_t req, uint32_t val, uint32_t idx, uint8_t *data, uint8_t len)
{
	int32_t res;

	if (!handle) {
		return -1;
	}

	res = libusb_control_transfer(handle, req_type, req, val, idx, data, len, 200);

	char *dir;

	if (req_type == 64) {
		dir = "writing";
	} else {
		dir = "reading";
	}

	printf("\tdevice_control_msg %i %s: 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X\n",
					req_type, dir, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);

	return res;
}

void camac_encode(uint32_t D, uint8_t A, uint8_t F, uint8_t N, uint8_t wait, uint8_t *dst_buf)
{
	div_t n;
	unsigned char LO, MD, HI;

	printf("camac_encode D=%u A=%i F=%i N=%i\n", D, A, F, N);

	n = div(D, 256);
	LO = n.rem;

	n = div(n.quot, 256);
	MD = n.rem;

	n = div(n.quot, 256);
	HI = n.rem;

	dst_buf[0] = HI;
	dst_buf[1] = MD;
	dst_buf[2] = LO;
	dst_buf[3] = A;
	dst_buf[4] = F;
	dst_buf[5] = N;
	dst_buf[6] = 0;
	dst_buf[7] = wait; 
}

int CommMUP(struct libusb_device_handle *handle, int ComMod, int koor)
{
	int err;
	uint8_t data_len = 8;
	uint8_t data_buf[data_len];

	switch (ComMod) {
		case CorrOff:
			camac_encode(1, A0, F9, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case CorrOn:
			camac_encode(1, A1, F9, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case SignOsP:
			camac_encode(1, A0, F17, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case SignOsM:
			camac_encode(1, A1, F17, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case DisSlow:
			camac_encode(1, A0, F18, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case EnbSlow:
			camac_encode(1, A1, F18, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case SlowOn:
			camac_encode(1, A1, F25, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case SlowOff:
			camac_encode(1, A0, F17, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case FastOnP:
			camac_encode(1, A2, F25, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;
	
		case FastOnM:
			camac_encode(1, A3, F25, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case FastOff:
			camac_encode(1, A4, F25, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case DislVk1:
			camac_encode(1, A0, F24, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case DislVk2:
			camac_encode(1, A1, F24, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case DisStyk:
			camac_encode(1, A2, F24, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case EnblVk1:
			camac_encode(1, A0, F26, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case EnblVk2:
			camac_encode(1, A1, F26, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		case EnbStyk:
			camac_encode(1, A2, F26, nMup[koor], 0, data_buf);
			err = device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, data_len);
			break;

		default:
			break;
	}

	return err;
}

void CamacSetZ(struct libusb_device_handle *handle)
{
	uint8_t data_buf[8] = { 0 };
	data_buf[0] = CAM_Z;

	device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB2, 0, 0, data_buf, 8);

	memset(data_buf, 0, 8);

	device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_FROM_DEVICE, 0xB9, 0, 0, data_buf, 8);
}

void CamacSetC(struct libusb_device_handle *handle)
{
	uint8_t data_buf[8] = { 0 };
	data_buf[0] = CAM_C;

	device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB2, 0, 0, data_buf, 8);
}

void CamacSetI(struct libusb_device_handle *handle)
{
	uint8_t data_buf[8] = { 0 };
	data_buf[0] = CAM_I;

	device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB2, 0, 0, data_buf, 8);
}

void CamacReset(struct libusb_device_handle *handle)
{
	uint8_t data_buf[8] = { 0 };
	data_buf[0] = CAM_Ax4;

	device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB2, 0, 0, data_buf, 8);

	memset(data_buf, 0, 8);

	device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_FROM_DEVICE, 0xB9, 0, 0, data_buf, 8);
}

void WriteVelocity(struct libusb_device_handle *handle, int Vel[4])
{
	coordinate koor, Bkoor, Ekoor;
	uint8_t data_buf[8] = { 0 };

	Bkoor = AS;
	Ekoor = ZN;

	char codeVel;

	for (koor = Bkoor; koor <= Ekoor; koor++) {
		codeVel = abs(Vel[koor]);

		camac_encode(codeVel, A0, F16, nSint[koor], 0, data_buf);
		device_control_msg(handle, TGT_DEVICE | REQ_VENDOR | DIR_TO_DEVICE, 0xB7, 0, 0, data_buf, 8);
	}
}

/// 
/// coor: 0 - Azimuth south section
///	      1 - Elevation south section
void FastDriverControl(struct libusb_device_handle *handle, uint8_t enable, uint8_t plus, coordinate coor)
{
	if (enable) {
		int dir = plus ? FastOnP : FastOnM;
		CommMUP(handle, dir, coor);
	} else {
		CommMUP(handle, FastOff, coor);
	}
}

int main()
{
	libusb_init(NULL);

	printf("Trying to open USB device with vid=0x0547 and pid=0x1002 ...\n");

	struct libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, 0x0547, 0x1002);

	if (!handle) {
		printf("Failed to open USB device, %s", strerror(errno));
		return -1;
	}

	if( libusb_kernel_driver_active(handle, 0)) {
        libusb_detach_kernel_driver(handle, 0);
	}

    int open_status = libusb_set_configuration(handle, 1);
    (void)open_status;

	printf("Device succesfully opened and configured, ready to work with CAMAC\n");

///

	printf("\nResetting CRATE controller\n");
	CamacReset(handle);

	printf("\nInitializing CRATE controller\n");
	CamacSetZ(handle);


///

	printf("\nSetting ZERO velocity for all channels\n");

	int V[4] = { 0,0,0,0 };
	WriteVelocity(handle, V);

///

	coordinate koor, Bkoor, Ekoor;
	Bkoor = AS;
	Ekoor = ZN;

	for (koor = Bkoor; koor <= Ekoor; koor++) {
		printf("\nDisable correction on ch %i\n", koor);
		CommMUP(handle, CorrOff, koor);

		printf("Unblock LAM signal on ch %i\n", koor);
		CommMUP(handle, EnblVk1, koor);
		CommMUP(handle, EnblVk2, koor);
		CommMUP(handle, EnbStyk, koor);

		printf("Disable slow driver on ch %i\n", koor);	
		CommMUP(handle, DisSlow, koor);

		printf("Poweroff slow driver on ch %i\n", koor);	
		CommMUP(handle, SlowOff, koor);
	}

///

	libusb_release_interface(handle, 0);
	libusb_close(handle);

	libusb_exit(NULL);

	return 0;
}

