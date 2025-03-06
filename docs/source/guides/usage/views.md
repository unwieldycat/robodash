# Views

Robodash provides the views API for other LVGL-powered GUIs to plug into its
view-management system.

Below is an example on creating a view called "my view".

```cpp
rd_view_t *view = rd_view_create("my view");
```

Creating a view will return a pointer to an `rd_view_t`, which holds the name of
the view and the LVGL object for the view. The name passed to the view
constructor will be the name that is displayed on screen in the view switcher
and any alert dialogues spawned by the view. The view's LVGL object should
parent any LVGL UI that is a part of that view, since this is how Robodash
changes which view is currently active on the screen. **Any instance of
`lv_scr_act()` in your LVGL GUI code should be replaced with
`lv_view_obj(your_view)`.**

The following is an example of a simple view that displays a text label.

```cpp
rd_view_t *view = rd_view_create("custom view");
lv_label_t *label = lv_label_create(rd_view_obj(view));
lv_label_set_text(label, "example");
lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
```

[Views API Reference](../../api/view.md) page.
