// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"
#include "lvgl.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Home_Screen;
lv_obj_t * ui_Telescope_Header1;
lv_obj_t * ui_Info_Container;
lv_obj_t * ui_Info_Panel;
lv_obj_t * ui_Time;
lv_obj_t * ui_Notif_counter;
lv_obj_t * ui_Mail_Counter;
lv_obj_t * ui_Mail_Symbol;
lv_obj_t * ui_Date;
lv_obj_t * ui_Home_Screen_Alt;
lv_obj_t * ui_Telescope_Header2;
lv_obj_t * ui_Info_Container1;
lv_obj_t * ui_Time1;
lv_obj_t * ui_Notif_counter1;
lv_obj_t * ui_Mail_Counter1;
lv_obj_t * ui_Mail_Symbol1;
lv_obj_t * ui_Home_Screen_Alt_2;
lv_obj_t * ui_Telescope_Header3;
lv_obj_t * ui_Bottom_Panel;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Info_Container2;
lv_obj_t * ui_Time2;
lv_obj_t * ui_Notif_counter2;
lv_obj_t * ui_Mail_Counter2;
lv_obj_t * ui_Mail_Symbol2;
lv_obj_t * ui_Home_Screen_Alt_3;
lv_obj_t * ui_Telescope_Header4;
lv_obj_t * ui_Bottom_Panel1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Info_Container3;
lv_obj_t * ui_Info_Panel1;
lv_obj_t * ui_Time3;
lv_obj_t * ui_Notif_counter3;
lv_obj_t * ui_Mail_Counter3;
lv_obj_t * ui_Mail_Symbol3;
lv_obj_t * ui_Date1;
lv_obj_t * ui_Enter_Voice_Command;
lv_obj_t * ui_Telescope_Header8;
lv_obj_t * ui_Say_Hey_Computer;
lv_obj_t * ui_Label3;
lv_obj_t * ui_Enter_Voice_Command_2;
lv_obj_t * ui_EnterVoiceCmdP2Text;
lv_obj_t * ui_Say_Hey_Computer1;
lv_obj_t * ui_EnterVoiceCmdP2Header;
lv_obj_t * ui_EnterVoiceCmdP2Content;
lv_obj_t * ui_Telescope_Header11;
lv_obj_t * ui_Enter_Voice_Command_3;
lv_obj_t * ui_Telescope_Header7;
lv_obj_t * ui_ContainerBelowHeader8;
lv_obj_t * ui_Label11;
lv_obj_t * ui_Label10;
lv_obj_t * ui_Label9;
lv_obj_t * ui_Card_Notification;
lv_obj_t * ui_Card_Notification_ContainerBelow;
lv_obj_t * ui_Card_with_icon1;
lv_obj_t * ui_Telescope_Header5;
lv_obj_t * ui_Card_Search_Textonly;
lv_obj_t * ui_Card_Search_TextOnly;
lv_obj_t * ui_ContainerBelowHeader7;
lv_obj_t * ui_CardSearchTextonlyContent;
lv_obj_t * ui_Card_Title_Text1;
lv_obj_t * ui_Card_Search_Hor;
lv_obj_t * ui_Telescope_Header10;
lv_obj_t * ui_ContainerBelowHeader1;
lv_obj_t * ui_ContainerBelowHeader3;
lv_obj_t * ui_Label8;
lv_obj_t * ui_Label7;
lv_obj_t * ui_ContainerBelowHeader2;
lv_obj_t * ui_Label6;
lv_obj_t * ui_Image2;
lv_obj_t * ui_Card_Search_Ver;
lv_obj_t * ui_Telescope_Header6;
lv_obj_t * ui_ContainerBelowHeader4;
lv_obj_t * ui_ContainerBelowHeader6;
lv_obj_t * ui_Image1;
lv_obj_t * ui_TapForMore;
lv_obj_t * ui_ContainerBelowHeader5;
lv_obj_t * ui_Content;
lv_obj_t * ui_Title;

lv_obj_t *ui_Card_Live_Captions;
lv_obj_t *ui_Card_Live_Captions_Header;
lv_obj_t *ui_ContainerBelowHeader1;
lv_obj_t *ui_Card_Live_Captions_Title;
lv_obj_t *ui_Card_Live_Captions_Content;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
//TODO:
//#if LV_COLOR_16_SWAP !=1
//    #error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
//#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_Home_Screen_screen_init(void)
{
    ui_Home_Screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Home_Screen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags

    ui_Telescope_Header1 = ui_Telescope_Header_create(ui_Home_Screen);
    lv_obj_set_x(ui_Telescope_Header1, 0);
    lv_obj_set_y(ui_Telescope_Header1, 0);

    ui_Info_Container = lv_obj_create(ui_Home_Screen);
    lv_obj_set_width(ui_Info_Container, lv_pct(100));
    lv_obj_set_height(ui_Info_Container, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Info_Container, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Info_Container, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Info_Container, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Info_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Info_Container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Info_Panel = lv_obj_create(ui_Info_Container);
    lv_obj_set_width(ui_Info_Panel, lv_pct(54));
    lv_obj_set_height(ui_Info_Panel, LV_SIZE_CONTENT);    /// 15
    lv_obj_set_align(ui_Info_Panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Info_Panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Info_Panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Info_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Info_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Info_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Info_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Info_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Info_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Time = lv_label_create(ui_Info_Panel);
    lv_obj_set_width(ui_Time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Time, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_Time, "02\n52");
    lv_obj_clear_flag(ui_Time, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    #if LV_FONT_MONTSERRAT_48
        lv_obj_set_style_text_font(ui_Time, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    #endif
    lv_obj_set_style_pad_left(ui_Time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Time, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Notif_counter = lv_obj_create(ui_Info_Panel);
    lv_obj_set_width(ui_Notif_counter, LV_SIZE_CONTENT);   /// 54
    lv_obj_set_height(ui_Notif_counter, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Notif_counter, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_Notif_counter, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_bg_color(ui_Notif_counter, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Notif_counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Notif_counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Notif_counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Notif_counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Notif_counter, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Notif_counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Counter = lv_label_create(ui_Notif_counter);
    lv_obj_set_width(ui_Mail_Counter, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Counter, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Counter, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Mail_Counter, "3");
    lv_obj_set_style_text_align(ui_Mail_Counter, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Counter, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Counter, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Counter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Symbol = lv_label_create(ui_Notif_counter);
    lv_obj_set_width(ui_Mail_Symbol, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Symbol, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Symbol, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_Mail_Symbol, "");
    lv_obj_set_style_text_align(ui_Mail_Symbol, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Symbol, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Symbol, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Symbol, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Symbol, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Symbol, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date = lv_label_create(ui_Info_Panel);
    lv_obj_set_width(ui_Date, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Date, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Date, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_Date, "Thu, October 6th");
    lv_obj_set_style_text_font(ui_Date, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Date, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Home_Screen_Alt_screen_init(void)
{
    ui_Home_Screen_Alt = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Home_Screen_Alt,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags

    ui_Telescope_Header2 = ui_Telescope_Header_create(ui_Home_Screen_Alt);
    lv_obj_set_x(ui_Telescope_Header2, 0);
    lv_obj_set_y(ui_Telescope_Header2, 0);

    ui_Info_Container1 = lv_obj_create(ui_Home_Screen_Alt);
    lv_obj_set_width(ui_Info_Container1, lv_pct(100));
    lv_obj_set_height(ui_Info_Container1, lv_pct(100));
    lv_obj_set_align(ui_Info_Container1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Info_Container1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Info_Container1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Info_Container1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Info_Container1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Info_Container1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Info_Container1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Info_Container1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Info_Container1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Time1 = lv_label_create(ui_Info_Container1);
    lv_obj_set_width(ui_Time1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Time1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Time1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Time1, "02:52 pm");
    lv_obj_clear_flag(ui_Time1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Time1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    #if LV_FONT_MONTSERRAT_48
        lv_obj_set_style_text_font(ui_Time1, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    #endif

    ui_Notif_counter1 = lv_obj_create(ui_Info_Container1);
    lv_obj_set_width(ui_Notif_counter1, LV_SIZE_CONTENT);   /// 54
    lv_obj_set_height(ui_Notif_counter1, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Notif_counter1, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Notif_counter1,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_bg_color(ui_Notif_counter1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Notif_counter1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Notif_counter1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Counter1 = lv_label_create(ui_Notif_counter1);
    lv_obj_set_width(ui_Mail_Counter1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Counter1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Counter1, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Mail_Counter1, "3");
    lv_obj_set_style_text_align(ui_Mail_Counter1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Counter1, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Counter1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Counter1, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Counter1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Counter1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Symbol1 = lv_label_create(ui_Notif_counter1);
    lv_obj_set_width(ui_Mail_Symbol1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Symbol1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Symbol1, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_Mail_Symbol1, "");
    lv_obj_set_style_text_align(ui_Mail_Symbol1, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Symbol1, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Symbol1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Symbol1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Symbol1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Symbol1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Home_Screen_Alt_2_screen_init(void)
{
    ui_Home_Screen_Alt_2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Home_Screen_Alt_2,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags

    ui_Telescope_Header3 = ui_Telescope_Header_create(ui_Home_Screen_Alt_2);
    lv_obj_set_x(ui_Telescope_Header3, 0);
    lv_obj_set_y(ui_Telescope_Header3, 0);

    ui_Bottom_Panel = lv_obj_create(ui_Home_Screen_Alt_2);
    lv_obj_set_height(ui_Bottom_Panel, 50);
    lv_obj_set_width(ui_Bottom_Panel, lv_pct(100));
    lv_obj_set_align(ui_Bottom_Panel, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Bottom_Panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Bottom_Panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Bottom_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Bottom_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_Bottom_Panel);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Say \"Hey Computer...\"");
    lv_obj_set_style_text_align(ui_Label1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Info_Container2 = lv_obj_create(ui_Home_Screen_Alt_2);
    lv_obj_set_width(ui_Info_Container2, lv_pct(100));
    lv_obj_set_height(ui_Info_Container2, lv_pct(100));
    lv_obj_set_align(ui_Info_Container2, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_Info_Container2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Info_Container2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Info_Container2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Info_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Info_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Info_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Info_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Info_Container2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Time2 = lv_label_create(ui_Info_Container2);
    lv_obj_set_width(ui_Time2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Time2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Time2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Time2, "02:52 pm");
    lv_obj_clear_flag(ui_Time2, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Time2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    #if LV_FONT_MONTSERRAT_48
        lv_obj_set_style_text_font(ui_Time2, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    #endif

    ui_Notif_counter2 = lv_obj_create(ui_Info_Container2);
    lv_obj_set_width(ui_Notif_counter2, LV_SIZE_CONTENT);   /// 54
    lv_obj_set_height(ui_Notif_counter2, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Notif_counter2, 0);
    lv_obj_set_y(ui_Notif_counter2, 50);
    lv_obj_set_align(ui_Notif_counter2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Notif_counter2,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_bg_color(ui_Notif_counter2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Notif_counter2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Notif_counter2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Counter2 = lv_label_create(ui_Notif_counter2);
    lv_obj_set_width(ui_Mail_Counter2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Counter2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Counter2, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Mail_Counter2, "3");
    lv_obj_set_style_text_align(ui_Mail_Counter2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Counter2, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Counter2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Counter2, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Counter2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Counter2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Symbol2 = lv_label_create(ui_Notif_counter2);
    lv_obj_set_width(ui_Mail_Symbol2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Symbol2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Symbol2, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_Mail_Symbol2, "");
    lv_obj_set_style_text_align(ui_Mail_Symbol2, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Symbol2, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Symbol2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Symbol2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Symbol2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Symbol2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Home_Screen_Alt_3_screen_init(void)
{
    ui_Home_Screen_Alt_3 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Home_Screen_Alt_3,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags
    lv_obj_set_style_bg_color(ui_Home_Screen_Alt_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Home_Screen_Alt_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Telescope_Header4 = ui_Telescope_Header_create(ui_Home_Screen_Alt_3);
    lv_obj_set_x(ui_Telescope_Header4, 0);
    lv_obj_set_y(ui_Telescope_Header4, 0);

    ui_Bottom_Panel1 = lv_obj_create(ui_Home_Screen_Alt_3);
    lv_obj_set_height(ui_Bottom_Panel1, 50);
    lv_obj_set_width(ui_Bottom_Panel1, lv_pct(100));
    lv_obj_set_align(ui_Bottom_Panel1, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Bottom_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Bottom_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Bottom_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Bottom_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label2 = lv_label_create(ui_Bottom_Panel1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Say \"Hey Computer...\"");
    lv_obj_set_style_text_align(ui_Label2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Info_Container3 = lv_obj_create(ui_Home_Screen_Alt_3);
    lv_obj_set_width(ui_Info_Container3, lv_pct(100));
    lv_obj_set_height(ui_Info_Container3, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Info_Container3, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Info_Container3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Info_Container3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Info_Container3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Info_Container3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Info_Panel1 = lv_obj_create(ui_Info_Container3);
    lv_obj_set_width(ui_Info_Panel1, lv_pct(54));
    lv_obj_set_height(ui_Info_Panel1, LV_SIZE_CONTENT);    /// 15
    lv_obj_set_align(ui_Info_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Info_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Info_Panel1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Info_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Info_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Info_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Info_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Info_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Info_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Time3 = lv_label_create(ui_Info_Panel1);
    lv_obj_set_width(ui_Time3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Time3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Time3, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_Time3, "02\n52");
    lv_obj_clear_flag(ui_Time3, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_text_align(ui_Time3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    #if LV_FONT_MONTSERRAT_48
        lv_obj_set_style_text_font(ui_Time3, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    #endif
    lv_obj_set_style_pad_left(ui_Time3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Time3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Time3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Time3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Notif_counter3 = lv_obj_create(ui_Info_Panel1);
    lv_obj_set_width(ui_Notif_counter3, LV_SIZE_CONTENT);   /// 54
    lv_obj_set_height(ui_Notif_counter3, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_align(ui_Notif_counter3, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_Notif_counter3,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_style_bg_color(ui_Notif_counter3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Notif_counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Notif_counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Notif_counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Notif_counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Notif_counter3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Notif_counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Counter3 = lv_label_create(ui_Notif_counter3);
    lv_obj_set_width(ui_Mail_Counter3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Counter3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Counter3, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Mail_Counter3, "3");
    lv_obj_set_style_text_align(ui_Mail_Counter3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Counter3, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Counter3, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Counter3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Mail_Symbol3 = lv_label_create(ui_Notif_counter3);
    lv_obj_set_width(ui_Mail_Symbol3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Mail_Symbol3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Mail_Symbol3, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_Mail_Symbol3, "");
    lv_obj_set_style_text_align(ui_Mail_Symbol3, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Mail_Symbol3, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Mail_Symbol3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Mail_Symbol3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Mail_Symbol3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Mail_Symbol3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date1 = lv_label_create(ui_Info_Panel1);
    lv_obj_set_width(ui_Date1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Date1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Date1, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_Date1, "Thu, October 6th");
    lv_obj_set_style_text_font(ui_Date1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Date1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Date1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Date1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Date1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Enter_Voice_Command_screen_init(void)
{
    ui_Enter_Voice_Command = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Enter_Voice_Command,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags
    lv_obj_set_style_bg_color(ui_Enter_Voice_Command, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Enter_Voice_Command, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Telescope_Header8 = ui_Telescope_Header_create(ui_Enter_Voice_Command);
    lv_obj_set_x(ui_Telescope_Header8, 0);
    lv_obj_set_y(ui_Telescope_Header8, 0);

    ui_Say_Hey_Computer = lv_obj_create(ui_Enter_Voice_Command);
    lv_obj_set_height(ui_Say_Hey_Computer, 50);
    lv_obj_set_width(ui_Say_Hey_Computer, lv_pct(100));
    lv_obj_set_align(ui_Say_Hey_Computer, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Say_Hey_Computer, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Say_Hey_Computer, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Say_Hey_Computer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Say_Hey_Computer, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label3 = lv_label_create(ui_Say_Hey_Computer);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "Say \"Hey Computer...\"");
    lv_obj_set_style_text_align(ui_Label3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Enter_Voice_Command_2_screen_init(void)
{
    ui_Enter_Voice_Command_2 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Enter_Voice_Command_2,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags

    ui_EnterVoiceCmdP2Text = lv_obj_create(ui_Enter_Voice_Command_2);
    lv_obj_set_width(ui_EnterVoiceCmdP2Text, lv_pct(100));
    lv_obj_set_height(ui_EnterVoiceCmdP2Text, lv_pct(100));
    lv_obj_set_align(ui_EnterVoiceCmdP2Text, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_EnterVoiceCmdP2Text, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_EnterVoiceCmdP2Text, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_EnterVoiceCmdP2Text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_EnterVoiceCmdP2Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Say_Hey_Computer1 = lv_obj_create(ui_EnterVoiceCmdP2Text);
    lv_obj_set_width(ui_Say_Hey_Computer1, lv_pct(100));
    lv_obj_set_height(ui_Say_Hey_Computer1, LV_SIZE_CONTENT);    /// 50
    lv_obj_set_x(ui_Say_Hey_Computer1, -5);
    lv_obj_set_y(ui_Say_Hey_Computer1, -61);
    lv_obj_set_align(ui_Say_Hey_Computer1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Say_Hey_Computer1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Say_Hey_Computer1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Say_Hey_Computer1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Say_Hey_Computer1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EnterVoiceCmdP2Header = lv_label_create(ui_Say_Hey_Computer1);
    lv_obj_set_width(ui_EnterVoiceCmdP2Header, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_EnterVoiceCmdP2Header, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_EnterVoiceCmdP2Header, LV_ALIGN_CENTER);
    lv_label_set_text(ui_EnterVoiceCmdP2Header, "\"Hey Computer\"");
    lv_obj_set_style_text_align(ui_EnterVoiceCmdP2Header, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_EnterVoiceCmdP2Header, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_EnterVoiceCmdP2Content = lv_label_create(ui_EnterVoiceCmdP2Text);
    lv_obj_set_width(ui_EnterVoiceCmdP2Content, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_EnterVoiceCmdP2Content, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_EnterVoiceCmdP2Content, 0);
    lv_obj_set_y(ui_EnterVoiceCmdP2Content, 40);
    lv_obj_set_align(ui_EnterVoiceCmdP2Content, LV_ALIGN_CENTER);
    lv_label_set_text(ui_EnterVoiceCmdP2Content,
                      "run contextual search\nrun speech translate ...\nrun live life captions\nrun blank screen");
    lv_obj_set_style_text_letter_space(ui_EnterVoiceCmdP2Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_EnterVoiceCmdP2Content, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_EnterVoiceCmdP2Content, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Telescope_Header11 = ui_Telescope_Header_create(ui_Enter_Voice_Command_2);
    lv_obj_set_x(ui_Telescope_Header11, 0);
    lv_obj_set_y(ui_Telescope_Header11, 0);

}
void ui_Enter_Voice_Command_3_screen_init(void)
{
    ui_Enter_Voice_Command_3 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Enter_Voice_Command_3,
                      LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags
    lv_obj_set_style_bg_color(ui_Enter_Voice_Command_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Enter_Voice_Command_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Telescope_Header7 = ui_Telescope_Header_create(ui_Enter_Voice_Command_3);
    lv_obj_set_x(ui_Telescope_Header7, 0);
    lv_obj_set_y(ui_Telescope_Header7, 0);

    ui_ContainerBelowHeader8 = ui_ContainerBelowHeader_create(ui_Enter_Voice_Command_3);
    lv_obj_set_x(ui_ContainerBelowHeader8, 0);
    lv_obj_set_y(ui_ContainerBelowHeader8, lv_pct(7));

    ui_Label11 = lv_label_create(ui_ContainerBelowHeader8);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label11, 0);
    lv_obj_set_y(ui_Label11, -40);
    lv_obj_set_align(ui_Label11, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Label11, "Then say 'finish command'");
    lv_obj_set_style_text_letter_space(ui_Label11, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_Label11, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label11, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label10 = lv_label_create(ui_ContainerBelowHeader8);
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "speech translate french");
    lv_obj_set_style_text_letter_space(ui_Label10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_Label10, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label10, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label9 = lv_label_create(ui_ContainerBelowHeader8);
    lv_obj_set_width(ui_Label9, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label9, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label9, 0);
    lv_obj_set_y(ui_Label9, 40);
    lv_obj_set_align(ui_Label9, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label9, "Run ...");
    lv_obj_set_style_text_align(ui_Label9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label9, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Card_Notification_screen_init(void)
{
    ui_Card_Notification = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Card_Notification, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Card_Notification_ContainerBelow = ui_ContainerBelowHeader_create(ui_Card_Notification);
    lv_obj_set_x(ui_Card_Notification_ContainerBelow, 0);
    lv_obj_set_y(ui_Card_Notification_ContainerBelow, lv_pct(7));

    ui_Card_with_icon1 = ui_NotificationCard_create(ui_Card_Notification_ContainerBelow);
    lv_obj_set_x(ui_Card_with_icon1, 0);
    lv_obj_set_y(ui_Card_with_icon1, 0);

    //lv_img_set_src(ui_comp_get_child(ui_Card_with_icon1, UI_COMP_NOTIFICATIONCARD_CARD_HERO), &ui_img_matt_shades_png);

    ui_Telescope_Header5 = ui_Telescope_Header_create(ui_Card_Notification);
    lv_obj_set_x(ui_Telescope_Header5, 0);
    lv_obj_set_y(ui_Telescope_Header5, 0);

}
void ui_Card_Search_Textonly_screen_init(void)
{
    ui_Card_Search_Textonly = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Card_Search_Textonly, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Card_Search_Textonly, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Card_Search_Textonly, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Card_Search_TextOnly = ui_Telescope_Header_create(ui_Card_Search_Textonly);
    lv_obj_set_x(ui_Card_Search_TextOnly, 0);
    lv_obj_set_y(ui_Card_Search_TextOnly, 0);

    ui_ContainerBelowHeader7 = ui_ContainerBelowHeader_create(ui_Card_Search_Textonly);
    lv_obj_set_x(ui_ContainerBelowHeader7, 0);
    lv_obj_set_y(ui_ContainerBelowHeader7, lv_pct(7));

    ui_CardSearchTextonlyContent = lv_label_create(ui_ContainerBelowHeader7);
    lv_obj_set_width(ui_CardSearchTextonlyContent, lv_pct(100));
    lv_obj_set_height(ui_CardSearchTextonlyContent, lv_pct(85));
    lv_obj_set_align(ui_CardSearchTextonlyContent, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_long_mode(ui_CardSearchTextonlyContent, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_CardSearchTextonlyContent,
                      "Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2 (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.");
    lv_obj_set_style_text_font(ui_CardSearchTextonlyContent, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Card_Title_Text1 = lv_label_create(ui_ContainerBelowHeader7);
    lv_obj_set_width(ui_Card_Title_Text1, lv_pct(100));
    lv_obj_set_height(ui_Card_Title_Text1, LV_SIZE_CONTENT);    /// 1
    lv_label_set_long_mode(ui_Card_Title_Text1, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_Card_Title_Text1, "Wikipedia - COVID-19");
    lv_obj_set_style_text_font(ui_Card_Title_Text1, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

}
void ui_Card_Search_Hor_screen_init(void)
{
    ui_Card_Search_Hor = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Card_Search_Hor, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Card_Search_Hor, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Card_Search_Hor, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Telescope_Header10 = ui_Telescope_Header_create(ui_Card_Search_Hor);
    lv_obj_set_x(ui_Telescope_Header10, 0);
    lv_obj_set_y(ui_Telescope_Header10, 0);

    ui_ContainerBelowHeader1 = ui_ContainerBelowHeader_create(ui_Card_Search_Hor);
    lv_obj_set_x(ui_ContainerBelowHeader1, 0);
    lv_obj_set_y(ui_ContainerBelowHeader1, lv_pct(7));

    ui_ContainerBelowHeader3 = lv_obj_create(ui_ContainerBelowHeader1);
    lv_obj_set_width(ui_ContainerBelowHeader3, lv_pct(40));
    lv_obj_set_height(ui_ContainerBelowHeader3, lv_pct(100));
    lv_obj_set_align(ui_ContainerBelowHeader3, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_ContainerBelowHeader3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ContainerBelowHeader3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ContainerBelowHeader3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerBelowHeader3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ContainerBelowHeader3, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ContainerBelowHeader3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ContainerBelowHeader3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ContainerBelowHeader3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label8 = lv_label_create(ui_ContainerBelowHeader3);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label8, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_Label8, "Tap for more");
    lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label7 = lv_label_create(ui_ContainerBelowHeader3);
    lv_obj_set_width(ui_Label7, lv_pct(100));
    lv_obj_set_height(ui_Label7, lv_pct(90));
    lv_label_set_long_mode(ui_Label7, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_Label7,
                      "Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2 (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.");
    lv_obj_set_style_text_align(ui_Label7, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ContainerBelowHeader2 = lv_obj_create(ui_ContainerBelowHeader1);
    lv_obj_set_width(ui_ContainerBelowHeader2, lv_pct(60));
    lv_obj_set_height(ui_ContainerBelowHeader2, lv_pct(100));
    lv_obj_set_align(ui_ContainerBelowHeader2, LV_ALIGN_LEFT_MID);
    lv_obj_clear_flag(ui_ContainerBelowHeader2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ContainerBelowHeader2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ContainerBelowHeader2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerBelowHeader2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ContainerBelowHeader2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ContainerBelowHeader2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ContainerBelowHeader2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ContainerBelowHeader2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label6 = lv_label_create(ui_ContainerBelowHeader2);
    lv_obj_set_width(ui_Label6, lv_pct(100));
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_label_set_long_mode(ui_Label6, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_label_set_text(ui_Label6, "Wikipedia - COVID-19");
    lv_obj_set_style_text_font(ui_Label6, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image2 = lv_img_create(ui_ContainerBelowHeader2);
    //lv_img_set_src(ui_Image2, &ui_img_test_png);
    lv_obj_set_width(ui_Image2, lv_pct(100));
    lv_obj_set_height(ui_Image2, lv_pct(80));
    lv_obj_set_align(ui_Image2, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}
void ui_Card_Search_Ver_screen_init(void)
{
    ui_Card_Search_Ver = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Card_Search_Ver, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Card_Search_Ver, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Card_Search_Ver, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Telescope_Header6 = ui_Telescope_Header_create(ui_Card_Search_Ver);
    lv_obj_set_x(ui_Telescope_Header6, 0);
    lv_obj_set_y(ui_Telescope_Header6, 0);

    ui_ContainerBelowHeader4 = ui_ContainerBelowHeader_create(ui_Card_Search_Ver);
    lv_obj_set_x(ui_ContainerBelowHeader4, 0);
    lv_obj_set_y(ui_ContainerBelowHeader4, lv_pct(7));

    ui_ContainerBelowHeader6 = lv_obj_create(ui_ContainerBelowHeader4);
    lv_obj_set_width(ui_ContainerBelowHeader6, lv_pct(50));
    lv_obj_set_height(ui_ContainerBelowHeader6, lv_pct(100));
    lv_obj_clear_flag(ui_ContainerBelowHeader6, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ContainerBelowHeader6, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ContainerBelowHeader6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerBelowHeader6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ContainerBelowHeader6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ContainerBelowHeader6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ContainerBelowHeader6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ContainerBelowHeader6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image1 = lv_img_create(ui_ContainerBelowHeader6);
    //lv_img_set_src(ui_Image1, &ui_img_test_png);
    lv_obj_set_width(ui_Image1, lv_pct(100));
    lv_obj_set_height(ui_Image1, lv_pct(100));
    lv_obj_set_align(ui_Image1, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TapForMore = lv_label_create(ui_ContainerBelowHeader4);
    lv_obj_set_width(ui_TapForMore, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TapForMore, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TapForMore, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_TapForMore, "Tap for more");
    lv_obj_set_style_text_font(ui_TapForMore, &lv_font_montserrat_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ContainerBelowHeader5 = lv_obj_create(ui_ContainerBelowHeader4);
    lv_obj_set_width(ui_ContainerBelowHeader5, lv_pct(50));
    lv_obj_set_height(ui_ContainerBelowHeader5, lv_pct(100));
    lv_obj_set_align(ui_ContainerBelowHeader5, LV_ALIGN_RIGHT_MID);
    lv_obj_clear_flag(ui_ContainerBelowHeader5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ContainerBelowHeader5, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ContainerBelowHeader5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_ContainerBelowHeader5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_ContainerBelowHeader5, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_ContainerBelowHeader5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_ContainerBelowHeader5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_ContainerBelowHeader5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Content = lv_label_create(ui_ContainerBelowHeader5);
    lv_obj_set_width(ui_Content, lv_pct(100));
    lv_obj_set_height(ui_Content, lv_pct(76));
    lv_obj_set_align(ui_Content, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_long_mode(ui_Content, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_Content,
                      "Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2 (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.");
    lv_obj_set_style_text_align(ui_Content, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Content, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Content, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Title = lv_label_create(ui_ContainerBelowHeader5);
    lv_obj_set_height(ui_Title, 50);
    lv_obj_set_width(ui_Title, lv_pct(100));
    lv_label_set_long_mode(ui_Title, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_Title, "Wikipedia\nCOVID-19");
    lv_obj_set_style_text_font(ui_Title, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_Card_Live_Captions_screen_init(void)
{
ui_Card_Live_Captions = lv_obj_create(NULL);
lv_obj_clear_flag( ui_Card_Live_Captions, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_Card_Live_Captions, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Card_Live_Captions, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Card_Live_Captions_Header = ui_Telescope_Header_create(ui_Card_Live_Captions);
lv_obj_set_x( ui_Card_Live_Captions_Header, 0 );
lv_obj_set_y( ui_Card_Live_Captions_Header, 0 );

ui_ContainerBelowHeader1 = ui_ContainerBelowHeader_create(ui_Card_Live_Captions);
lv_obj_set_x( ui_ContainerBelowHeader1, 0 );
lv_obj_set_y( ui_ContainerBelowHeader1, lv_pct(7) );

ui_Card_Live_Captions_Title = lv_label_create(ui_ContainerBelowHeader1);
lv_obj_set_width( ui_Card_Live_Captions_Title, lv_pct(100));
lv_obj_set_height( ui_Card_Live_Captions_Title, LV_SIZE_CONTENT);   /// 1
lv_label_set_long_mode(ui_Card_Live_Captions_Title,LV_LABEL_LONG_SCROLL_CIRCULAR);
lv_label_set_text(ui_Card_Live_Captions_Title,"Live Captions");
lv_obj_clear_flag( ui_Card_Live_Captions_Title, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_style_text_font(ui_Card_Live_Captions_Title, &lv_font_montserrat_22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Card_Live_Captions_Content = lv_label_create(ui_ContainerBelowHeader1);
lv_obj_set_width( ui_Card_Live_Captions_Content, lv_pct(100));
lv_obj_set_height( ui_Card_Live_Captions_Content, lv_pct(85));
lv_obj_set_align( ui_Card_Live_Captions_Content, LV_ALIGN_BOTTOM_LEFT );
lv_label_set_text(ui_Card_Live_Captions_Content,"Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.oronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.oronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.oronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.oronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.Coronavirus disease 2019 (COVID-19) is a contagious disease caused by a virus, the severe acute respiratory syndrome coronavirus 2sssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss (SARS-CoV-2). The first known case was identified in Wuhan, China, in December 2019.[7] The disease quickly spread worldwide, resulting in the COVID-19 pandemic.");
lv_obj_clear_flag( ui_Card_Live_Captions_Content, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN );    /// Flags
lv_obj_set_scrollbar_mode(ui_Card_Live_Captions_Content, LV_SCROLLBAR_MODE_OFF);
lv_obj_set_scroll_dir(ui_Card_Live_Captions_Content, LV_DIR_VER);
lv_obj_set_style_text_font(ui_Card_Live_Captions_Content, &lv_font_montserrat_18, LV_PART_MAIN| LV_STATE_DEFAULT);
}

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Home_Screen_screen_init();
    ui_Home_Screen_Alt_screen_init();
    ui_Home_Screen_Alt_2_screen_init();
    ui_Home_Screen_Alt_3_screen_init();
    ui_Enter_Voice_Command_screen_init();
    ui_Enter_Voice_Command_2_screen_init();
    ui_Enter_Voice_Command_3_screen_init();
    ui_Card_Notification_screen_init();
    ui_Card_Search_Textonly_screen_init();
    ui_Card_Search_Hor_screen_init();
    ui_Card_Search_Ver_screen_init();
    ui_Card_Live_Captions_screen_init();
    //lv_disp_load_scr(ui_Home_Screen);
}
