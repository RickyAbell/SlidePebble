#include <pebble.h>

static Window *window;

static TextLayer *previous_slide_text;
static TextLayer *next_slide_text;

static ActionBarLayer *action_bar_layer;

static GBitmap *previous_slide_button_image;
static GBitmap *next_slide_button_image;

enum {
  PREVIOUS_SLIDE_KEY = 0x0,
  NEXT_SLIDE_KEY = 0x1
};

static const char *PREVIOUS_SLIDE_STRING = "Previous Slide";
static const char *NEXT_SLIDE_STRING = "Next Slide";

static void send_message_to_phone(int message_key) {
  Tuplet message = TupletInteger(message_key, 1);

  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  dict_write_tuplet(iter, &message);
  dict_write_end(iter);

  app_message_outbox_send();
}

static void in_dropped_handler(AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message In Dropped: %d", app_message_error);
}

static void out_failed_handler(DictionaryIterator *failed, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Failed to Send: %d", app_message_error);
}

static void app_message_init(void) {
  //Register message handlers
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_failed(out_failed_handler);
  //Init buffers
  app_message_open(64, 64);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_message_to_phone(PREVIOUS_SLIDE_KEY);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  send_message_to_phone(NEXT_SLIDE_KEY);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void action_bar_init(Window *window) {
  action_bar_layer = action_bar_layer_create();

  action_bar_layer_add_to_window(action_bar_layer, window);
  action_bar_layer_set_background_color(action_bar_layer, GColorWhite);
  action_bar_layer_set_click_config_provider(action_bar_layer, click_config_provider);
  action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_UP, previous_slide_button_image);
  action_bar_layer_set_icon(action_bar_layer, BUTTON_ID_DOWN, next_slide_button_image);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  window_set_background_color(window, GColorBlack);

  //Load assets
  previous_slide_button_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PREVIOUS_BUTTON);
  next_slide_button_image = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NEXT_BUTTON);

  //Setup action bar
  action_bar_init(window);

  //Text layer for "Previous Slide"
  previous_slide_text = text_layer_create(GRect(8, 10, 110, 40));
  text_layer_set_text_color(previous_slide_text, GColorWhite);
  text_layer_set_background_color(previous_slide_text, GColorClear);
  text_layer_set_text(previous_slide_text, PREVIOUS_SLIDE_STRING);
  text_layer_set_font(previous_slide_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(previous_slide_text));

  //Text layer for "Next Slide"
  next_slide_text = text_layer_create(GRect(8, 107, 110, 40));
  text_layer_set_text_color(next_slide_text, GColorWhite);
  text_layer_set_background_color(next_slide_text, GColorClear);
  text_layer_set_text(next_slide_text, NEXT_SLIDE_STRING);
  text_layer_set_font(next_slide_text, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  layer_add_child(window_layer, text_layer_get_layer(next_slide_text));
}

static void window_unload(Window *window) {
  text_layer_destroy(previous_slide_text);
  text_layer_destroy(next_slide_text);
  
  gbitmap_destroy(previous_slide_button_image);
  gbitmap_destroy(next_slide_button_image);

  action_bar_layer_destroy(action_bar_layer);
}

static void deinit(void) {
  window_destroy(window);
}

static void init(void) {
  //Setup handlers and buffers for pebble to phone communication
  app_message_init();

  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });

  const bool animated = true;
  window_stack_push(window, animated /* Animated */);
}

int main(void) {
  init();

  app_event_loop();

  deinit();
}
