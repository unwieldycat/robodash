/*
    Based on the LVGL stdio fs template, with information from
    https://www.vexforum.com/t/lvgl-image-not-displaying/63612/14

    Used for opening images, but write is supported too
*/

#include "apix.h"
#include "liblvgl/lvgl.h"
#include <stdio.h>

// ========================= Function Declarations ========================= //

static void *fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode) {
	LV_UNUSED(drv);

	const char *flags = "";

	if (mode == LV_FS_MODE_WR)
		flags = "wb";
	else if (mode == LV_FS_MODE_RD)
		flags = "rb";
	else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
		flags = "rb+";

	char buf[256];
	sprintf(buf, "%s", path);

	return fopen(buf, flags);
}

static lv_fs_res_t fs_close(lv_fs_drv_t *drv, void *file_p) {
	LV_UNUSED(drv);
	fclose((FILE *)file_p);
	return LV_FS_RES_OK;
}

static lv_fs_res_t fs_read(lv_fs_drv_t *drv, void *file_p, void *buf, uint32_t btr, uint32_t *br) {
	LV_UNUSED(drv);
	*br = fread(buf, 1, btr, (FILE *)file_p);
	return (int32_t)(*br) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

static lv_fs_res_t
fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw) {
	LV_UNUSED(drv);
	*bw = fwrite(buf, 1, btw, (FILE *)file_p);
	return (int32_t)(*bw) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

static lv_fs_res_t fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence) {
	LV_UNUSED(drv);
	int w;
	switch (whence) {
	case LV_FS_SEEK_SET:
		w = SEEK_SET;
		break;
	case LV_FS_SEEK_CUR:
		w = SEEK_CUR;
		break;
	case LV_FS_SEEK_END:
		w = SEEK_END;
		break;
	default:
		return LV_FS_RES_INV_PARAM;
	}

	fseek((FILE *)file_p, pos, w);
	return LV_FS_RES_OK;
}

static lv_fs_res_t fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
	LV_UNUSED(drv);
	*pos_p = ftell((FILE *)file_p);
	return LV_FS_RES_OK;
}

static void *fs_dir_open(lv_fs_drv_t *drv, const char *path) { return NULL; }

static lv_fs_res_t fs_dir_read(lv_fs_drv_t *drv, void *rddir_p, char *fn) {
	return LV_FS_RES_NOT_IMP;
}

static lv_fs_res_t fs_dir_close(lv_fs_drv_t *drv, void *rddir_p) { return LV_FS_RES_NOT_IMP; }

// =============================== Initialize =============================== //

void _init_fs(void) {
	static lv_fs_drv_t fs_drv;
	lv_fs_drv_init(&fs_drv);

	fs_drv.letter = 'S';
	fs_drv.open_cb = fs_open;
	fs_drv.close_cb = fs_close;
	fs_drv.read_cb = fs_read;
	fs_drv.write_cb = fs_write;
	fs_drv.seek_cb = fs_seek;
	fs_drv.tell_cb = fs_tell;

	fs_drv.dir_close_cb = fs_dir_close;
	fs_drv.dir_open_cb = fs_dir_open;
	fs_drv.dir_read_cb = fs_dir_read;

	lv_fs_drv_register(&fs_drv);
}
