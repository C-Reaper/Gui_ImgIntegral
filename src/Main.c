#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/RLCamera.h"
#include "/home/codeleaded/System/Static/Library/ImageIntegral.h"


Rect target;
RLCamera rlc;
unsigned int track_sum; 

unsigned int Tracker_Counter(unsigned int pixel){
    //const Color c = { .p = pixel };
    //return (unsigned int)(c.r + c.g + c.b);
    return (unsigned int)(Pixel_Lightness_N(pixel) * 1000.0f);
}

void Setup(AlxWindow* w){
    rlc = RLCamera_New(RLCAMERA_DEVICE,w->Width,w->Height);
    track_sum = 0xFFFFFFFFU;
    target = Rect_New((Vec2){ 0.0f,0.0f },(Vec2){ 250.0f,250.0f });
}

void Update(AlxWindow* w){
    Sprite sp = Sprite_Null();
    sp.img = RLCamera_Get(&rlc,&sp.w,&sp.h);

    if(Stroke(ALX_MOUSE_L).DOWN){
        target.p.x = w->MouseX;
        target.p.y = w->MouseY;
        track_sum = 0xFFFFFFFFU;
    }else if(Stroke(ALX_KEY_W).DOWN){
        track_sum = 0xFFFFFFFFU;
        target.d.y -= 100.0f * w->ElapsedTime;
    }else if(Stroke(ALX_KEY_S).DOWN){
        track_sum = 0xFFFFFFFFU;
        target.d.y += 100.0f * w->ElapsedTime;
    }else if(Stroke(ALX_KEY_A).DOWN){
        track_sum = 0xFFFFFFFFU;
        target.d.x -= 100.0f * w->ElapsedTime;
    }else if(Stroke(ALX_KEY_D).DOWN){
        track_sum = 0xFFFFFFFFU;
        target.d.x += 100.0f * w->ElapsedTime;
    }else if(track_sum == 0xFFFFFFFFU){
        ImageIntegral ii = ImageIntegral_By(&sp,Tracker_Counter);
        track_sum = ImageIntegral_Area(&ii,target.p.x - target.d.x * 0.5f,target.p.y - target.d.y * 0.5f,target.d.x,target.d.y);
        ImageIntegral_Free(&ii);
    }else if(sp.img){
        ImageIntegral ii = ImageIntegral_By(&sp,Tracker_Counter);
        const int area4_x = (int)(target.d.x / 4);
        const int area4_y = (int)(target.d.y / 4);

        int g_min_sum = I32_MAX;
        Vec2 pos = { 0.0f,0.0f };

        for(int i = target.p.y - area4_y;i<target.p.y + area4_y;i++){
            for(int j = target.p.x - area4_x;j<target.p.x + area4_x;j++){
                const int px = j - target.d.x * 0.5f;
                const int py = i - target.d.y * 0.5f;
                const int c = ImageIntegral_Area(&ii,px,py,target.d.x,target.d.y);
                const int diff = I32_Abs(c - track_sum);

                if(diff < g_min_sum){
                    g_min_sum = diff;
                    pos.x = j;
                    pos.y = i;
                }
            }
        }
        
        target.p = pos;
        ImageIntegral_Free(&ii);
    }

    Clear(BLACK);

    if(sp.img){
        Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);
        Sprite_Free(&sp);
    }

    Rect_RenderXWire(WINDOW_STD_ARGS,Vec2_Sub(target.p,Vec2_Mulf(target.d,0.5f)),target.d,WHITE,1.0f);
}

void Delete(AlxWindow* w){
    RLCamera_Free(&rlc);
}

int main(){
    if(Create("Image Integral",800,600,2,2,Setup,Update,Delete))
        Start();
    return 0;
}