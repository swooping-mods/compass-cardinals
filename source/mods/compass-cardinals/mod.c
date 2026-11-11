#define FEATURE 23
#define MOD_ID "compass-cardinals"
#define HUD_Y 0
#define FW_NAME "Compass Cardinals"
#define FW_DESC "Adds cardinal bearings to the compass."
#define FW_PRICE 100
#include "runtime.h"
static DRoot letters[4];static int ribbon_ready;
static void feature_end(void){fw_clear();for(int i=0;i<4;i++)ddrop(letters+i);destroy_root(&m.ui);ddrop(&m.label);ribbon_ready=0;}
static void ribbon(float heading){
 if(!ui())return;int ok=1;PTR root=dget(m.ui),panel=0;PTR tr=call(m.go_tr,root,0,&ok);
 if(!ribbon_ready){
  const char *names[]={"N","E","S","W"};
  for(int i=0;i<4&&ok;i++){panel=go(names[i],tr,&ok);add(panel,"UnityEngine","RectTransform",&ok);PTR text=add(panel,"UnityEngine.UI","Text",&ok);letters[i]=dhold(text);void *a[]={da.string(names[i])};call(m.text,text,a,&ok);PTR font=call(mm("UnityEngine.UI","Text","get_font",""),dget(m.label),0,&ok);void *b[]={font};call(m.font,text,b,&ok);int sz=20,align=4;mset(m.font_size,text,&sz);mset(m.alignment,text,&align);DColor c={.65f,.95f,.85f,1};mset(m.color,text,&c);unsigned char no=0;mset(m.raycast,text,&no);}
  ribbon_ready=ok;
 }
 /* Each cardinal follows the native compass heading, wrapping around its
  * seam. The overlay's center is the player's actual forward bearing. */
 unsigned char visible=1;mset(m.active,root,&visible);
 for(int i=0;i<4;i++){PTR text=dget(letters[i]);if(!text)continue;float delta=moon_map_bearing_delta(i*90,heading);PTR goobj=call(mm("UnityEngine","Component","get_gameObject",""),text,0,&ok);PTR r=mc(goobj,"UnityEngine","RectTransform",&ok);V2 top={.5f,1},pos={delta*2,-34},size={30,30};mset(m.anchor_min,r,&top);mset(m.anchor_max,r,&top);V2 center={.5f,.5f};mset(m.pivot,r,&center);mset(m.anchored,r,&pos);mset(m.size,r,&size);DColor col={.65f,.95f,.85f,delta>=-85&&delta<=85?1:0};mset(m.color,text,&col);}
 /* The regular purchase panel is hidden while the thin ribbon is visible. */
 PTR labelgo=call(mm("UnityEngine","Component","get_gameObject",""),dget(m.label),0,&ok),labeltr=call(m.go_tr,labelgo,0,&ok),parent=call(mm("UnityEngine","Transform","get_parent",""),labeltr,0,&ok),panelgo=call(mm("UnityEngine","Component","get_gameObject",""),parent,0,&ok);unsigned char no=0;mset(m.active,panelgo,&no);
}
static void feature_tick(PTR walker,PTR world,int input){
 (void)world;(void)input;int ok=1,blocked=boolean(m.menu,walker,&ok);
 if(!m.owned||blocked||mapopen(map())){show("",0);fw_clear();return;}
 PTR compass=mc(walker,"MoonCleaners","MoonServiceCompass",&ok);float heading=compass?dnumber(mm("MoonCleaners","MoonServiceCompass","get_HeadingDegrees",""),compass,&ok):0;
 if(ok&&compass)ribbon(heading);else show("",0);
}
