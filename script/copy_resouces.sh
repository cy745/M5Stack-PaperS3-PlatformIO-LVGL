# 将 lvgl-editor 产生的静态资源拷贝至 filesystem 映射目录data

LVGL_RES_DIR="../lib/lvgl_ui/images"
TARGET_RES_DIR="../data/images"

function copy_resouces() {
    cp -rf "$LVGL_RES_DIR"/*.png "$TARGET_RES_DIR"
}

copy_resouces