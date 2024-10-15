## Views API

Robodash provides an API for other LVGL-powered GUIs to plug into its
view-management system.

<!-- TODO: Stuff here -->

The name passed to each view will be the name that is displayed on screen in the
view switcher and any alert dialogues spawned by the view.

The following is an example of a simple view that displays a text label.

```cpp
void opcontrol() {
   rd_view_t *view = rd_view_create("custom view");
   lv_label_t *label = lv_label_create(rd_view_obj(view));
   lv_label_set_text(label, "example");
   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
```

[Views API Reference](../api/core.md) page.
