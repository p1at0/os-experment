#include <gtk/gtk.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define INFO_MAX_LEN 512
#define PROC_MAX_LEN 128 
gboolean get_cur_time(gpointer data);

  enum{
    PID_COL,
    NAME_COL,
    STATE_COL,
    PPID_COL,
    PRIORITY_COL,
    TAKEUP_COL,
    N_COL
  };
// PC INFO
char* get_cpu_name(char*);
char* get_cpu_frequency(char*);
char* get_cpu_cores(char*);
char* get_cache_size(char*);
char* get_os_name(char*);
char* get_kernel_version(char*);
char* get_gcc_version(char*);
gboolean get_running_info(gpointer data);

// PROCESS
void get_proc_info(GtkListStore*);
void refresh_proc(GtkListStore*);
void kill_proc(void);

// Perfomance
/*
gboolean cpu_draw_callback(GtkWidget* widget);
gboolean cpu_draw(gpointer widget);
gboolean ram_draw_callback(GtkWidget* widget);
gboolean ram_draw(gpointer widget);
*/
gboolean cpu_draw_callback(GtkWidget*, cairo_t*, gpointer);
gboolean ram_draw_callback(GtkWidget* , cairo_t *, gpointer );


// ABOUT
char* get_username_and_hostname(char*);

int main(){
  
  GtkWidget* window;
  GtkWidget* table;
  GtkWidget* layout;
  GtkWidget* label_time;
  GtkWidget* fixed;
  GtkWidget* notebook;
  GtkWidget* label;
  GtkWidget* vbox;
  GtkWidget* hbox;
  GtkWidget* frame_1;
  GtkWidget* frame_2;
  GtkWidget* frame_3;
  GtkWidget* scrolled_window;
  GtkWidget* button_1;
  GtkWidget* button_2;
  GtkWidget* drawing_area_1;
  GtkWidget* drawing_area_2;
  GtkWidget* tree;

  GtkListStore* store;
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;

  char buf[INFO_MAX_LEN];
  char buf1[INFO_MAX_LEN], buf2[INFO_MAX_LEN], buf3[INFO_MAX_LEN];
  char _buf1[INFO_MAX_LEN], _buf2[INFO_MAX_LEN], _buf3[INFO_MAX_LEN], _buf4[INFO_MAX_LEN];
  
  

	gtk_init(NULL, NULL);
	// 创建窗口、笔记本
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Proc");
	gtk_widget_set_size_request(window, 650, 570);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  // gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  //*****************左下角信息 
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  label_time = gtk_label_new(NULL);
  g_timeout_add(1000, get_cur_time, (void*)label_time);
  label = gtk_label_new(NULL);
  sprintf(buf,"<span foreground='red' font_desc='12'>%s</span>", get_username_and_hostname(buf1));
  gtk_label_set_markup(GTK_LABEL(label), buf);
  fixed = gtk_fixed_new();
  gtk_box_pack_end(GTK_BOX(vbox), fixed, FALSE, FALSE, 0);
  gtk_fixed_put(GTK_FIXED(fixed), label, 0, 0);
  gtk_fixed_put(GTK_FIXED(fixed), label_time, 0, 20);
  // table = gtk_table_new(10, 8, FALSE);
  // gt//ik_container_add(GTK_CONTAINER(window), table);
  // gtk_box_pack_start(GTK_BOX(vbox), table, FALSE, FALSE, 0);
  // gtk_container_siijet_border_width(GTK_CONTAINER(table), 20);
  notebook = gtk_notebook_new(); 
  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook), GTK_POS_TOP);
  gtk_box_pack_start(GTK_BOX(vbox), notebook, FALSE, FALSE, 0);
  gtk_container_set_border_width(GTK_CONTAINER(notebook), 25);
  



  //*****************第一个标签页, 系统信息
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>os info</span>");
  frame_1 = gtk_frame_new(NULL);
  gtk_frame_set_label_widget(GTK_FRAME(frame_1), label);
  gtk_container_set_border_width(GTK_CONTAINER(frame_1), 1);
  gtk_widget_set_size_request(frame_1, 500, 140);
  sprintf(buf, "<span font_desc='12'>os name: %s\n\nkernel version: %s\n\ngcc version: %s</span>", get_os_name(_buf1), get_kernel_version(_buf2), get_gcc_version(_buf3));
  label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label), buf);
  gtk_container_add(GTK_CONTAINER(frame_1), label);
  gtk_frame_set_label_align(GTK_FRAME(frame_1), 0.5, 0.5);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>cpu info</span>");
  frame_2 = gtk_frame_new(NULL);
  gtk_frame_set_label_widget(GTK_FRAME(frame_2), label);
  gtk_container_set_border_width(GTK_CONTAINER(frame_2), 1);
  gtk_widget_set_size_request(frame_2, 500, 160);
  sprintf(buf, "<span font_desc='12'>cpu name: %s\n\ncpu frequency: %s\n\ncpu cores: %s\n\ncache size: %s</span>", get_cpu_name(_buf1), get_cpu_frequency(_buf2), get_cpu_cores(_buf3), get_cache_size(_buf4));
  label = gtk_label_new(NULL);
	gtk_label_set_markup(GTK_LABEL(label), buf);
  gtk_container_add(GTK_CONTAINER(frame_2), label);
  gtk_frame_set_label_align(GTK_FRAME(frame_2), 0.5, 0.5);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>running info</span>");
  frame_3 = gtk_frame_new(NULL);
  gtk_frame_set_label_widget(GTK_FRAME(frame_3), label);
  gtk_container_set_border_width(GTK_CONTAINER(frame_3), 1);
  gtk_widget_set_size_request(frame_3, 500, 100);
  label = gtk_label_new(NULL);
  g_timeout_add(1000, get_running_info, (void*)label);
  gtk_container_add(GTK_CONTAINER(frame_3), label);
  gtk_frame_set_label_align(GTK_FRAME(frame_3), 0.5, 0.5);
  gtk_box_pack_start(GTK_BOX(vbox), frame_1, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), frame_3, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(vbox), frame_2, FALSE, FALSE, 5);

  label = gtk_label_new("PC Info");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);


  //******************第二个标签页, 进程信息
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  scrolled_window = gtk_scrolled_window_new(NULL, NULL);

  store = gtk_list_store_new(N_COL, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
  get_proc_info(store);
  tree = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes ("PID", renderer, "text", PID_COL,NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tree), column);

  column = gtk_tree_view_column_new_with_attributes ("Name",renderer,"text", NAME_COL, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(tree), column);

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes ("State", renderer,"text", STATE_COL, NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);
  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes ("ppid", renderer, "text", PPID_COL,NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes ("priority", renderer, "text",PRIORITY_COL,NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes ("takeup", renderer, "text",TAKEUP_COL, NULL);
  gtk_tree_view_append_column (GTK_TREE_VIEW (tree), column);

  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
  gtk_container_add(GTK_CONTAINER(scrolled_window), tree);
  gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 5);
  // gtk_box_pack_start(GTK_BOX(vbox), tree, FALSE, FALSE, 5);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

  button_1 = gtk_button_new_with_label("Kill");
  gtk_widget_set_size_request(button_1, 100, 35);
  g_signal_connect(button_1, "clicked",G_CALLBACK(kill_proc), NULL);
  gtk_box_pack_end(GTK_BOX(hbox), button_1, FALSE, FALSE, 10);

  button_2 = gtk_button_new_with_label("Refresh");
  gtk_widget_set_size_request(button_2, 100, 35);
  g_signal_connect_swapped(button_2, "clicked", G_CALLBACK(refresh_proc), store);  
  gtk_box_pack_end(GTK_BOX(hbox), button_2, FALSE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);

  label = gtk_label_new("Process");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

  //**************************第三个标签页,Performance 
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_widget_set_size_request(vbox, 200, 300);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>CPU</span>");
  frame_1 = gtk_frame_new(NULL);
  gtk_frame_set_label_widget(GTK_FRAME(frame_1), label);
  gtk_frame_set_label_align(GTK_FRAME(frame_1), 0.5, 0.5);
  // drawing_area_1 = gtk_window_new() ;
  drawing_area_1 = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area_1, 100, 160);
  g_signal_connect(G_OBJECT(drawing_area_1), "draw", G_CALLBACK(cpu_draw_callback), NULL);
  gtk_container_add(GTK_CONTAINER(frame_1), drawing_area_1);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>RAM</span>");
  frame_2 = gtk_frame_new(NULL);
  gtk_frame_set_label_widget(GTK_FRAME(frame_2), label);
  gtk_frame_set_label_align(GTK_FRAME(frame_2), 0.5, 0.5);
  // drawing_area_2 = gtk_window_new();
  drawing_area_2 = gtk_drawing_area_new();
  gtk_widget_set_size_request(drawing_area_2, 100, 160);
  g_signal_connect(G_OBJECT(drawing_area_2), "draw", G_CALLBACK(ram_draw_callback), NULL);
  gtk_container_add(GTK_CONTAINER(frame_2), drawing_area_2);

  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  
  gtk_box_pack_start(GTK_BOX(vbox), frame_1, FALSE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), frame_2, FALSE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);


  
  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);


  label = gtk_label_new(NULL);
  g_timeout_add(2000, get_total_proc, (void*)label);
  gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 10);

  label = gtk_label_new(NULL);
  g_timeout_add(2000, get_cpu_usage, (void*)label);
  gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 10);

  label = gtk_label_new(NULL);
  g_timeout_add(2000, get_ram_usage, (void*)label);
  gtk_box_pack_start(GTK_BOX(hbox), label, FALSE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);

  
  label = gtk_label_new("Performance");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

  // 第四个标签页, About
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);


  fixed = gtk_fixed_new();
  gtk_box_pack_start(GTK_BOX(vbox), fixed, FALSE, FALSE, 10);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>@Author: zyh.p1at0@gmail.com</span>");
  gtk_fixed_put(GTK_FIXED(fixed), label, 170, 100);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>@LastModified: 2019-02-25</span>");
  gtk_fixed_put(GTK_FIXED(fixed), label, 170, 160);

  label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='14'>Coypright (c) 2019</span>");
  gtk_fixed_put(GTK_FIXED(fixed), label, 200, 220);


  label = gtk_label_new("About");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

	//  显示所有内容
	gtk_widget_show_all(window);
  // 主事件循环
  gtk_main();

  return 0;
}	
gboolean get_cur_time(gpointer data){
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);
	gchar *string_time = g_strdup_printf("<span foreground='red' font_desc='12'>%02d:%02d:%02d</span>", p->tm_hour, p->tm_min, p->tm_sec);
	gtk_label_set_markup(GTK_LABEL(data), string_time);
	return TRUE;	
}
char* get_cpu_name(char* _buf){
  FILE* fp = fopen("/proc/cpuinfo", "r");
  char* buf = _buf;
  int i = 0;
 
  //in No.5 line
  for(; i < 5; i++){
    fgets(buf, INFO_MAX_LEN, fp);
  }
  
  i = 0;
  while(buf[i++] != ':');
  i++;
  buf += i;
  i = 0;
  while(buf[i++] != '\n');
  buf[i-15] = '\0';
  fclose(fp);
  return buf;
}
char* get_cpu_frequency(char* _buf){
  FILE* fp = fopen("/proc/cpuinfo", "r");
  char* buf = _buf;
  int i = 0;
 
  //in No.5 line
  for(; i < 5; i++){
    fgets(buf, INFO_MAX_LEN, fp);
  }
  
  i = 0;
  while(buf[i++] != ':');
  i++;
  buf += i;
  i = 0;
  while(buf[i++] != '@');
  buf += i;
  i = 0;
  while(buf[i++] != '\n');
  buf[i-1] = '\0';
  fclose(fp);
  return buf;
}
char* get_cpu_cores(char* _buf){
  FILE* fp = fopen("/proc/cpuinfo", "r");
  char* buf = _buf;
  int i = 0;
 
  //in No.13 line
  for(; i < 13; i++){
    fgets(buf, INFO_MAX_LEN, fp);
  }
  
  i = 0;
  while(buf[i++] != ':');
  i++;
  buf += i;
  i = 0;
  while(buf[i++] != '\n');
  buf[i-1] = '\0';
  fclose(fp);
  return buf;
}
char* get_cache_size(char* _buf){
  FILE* fp = fopen("/proc/cpuinfo", "r");
  char* buf = _buf;
  int i = 0;
 
  //in No.9 line
  for(; i < 9; i++){
    fgets(buf, INFO_MAX_LEN, fp);
  }
  
  i = 0;
  while(buf[i++] != ':');
  i++;
  buf += i;
  i = 0;
  while(buf[i++] != '\n');
  buf[i-1] = '\0';
  fclose(fp);
  return buf;
}
char* get_os_name(char* _buf){
  FILE* fp = fopen("/etc/issue", "r");
  char* buf = _buf;
  int i = 0;

  fgets(buf, INFO_MAX_LEN, fp);

  while(buf[i++] != '\\');
  buf[i - 1] = '\0';
  fclose(fp);
  return buf;
}
char* get_kernel_version(char* _buf){
  FILE* fp = fopen("/proc/version", "r");
  char* buf = _buf;
  int start = 0; 
  int end = 0;
  int i = 0;
  int j = 0;
  int flag = 1; 

  fgets(buf, INFO_MAX_LEN, fp);
  while(flag){
    if(buf[i] == ' '){
      j++;
      if(j == 2){
        start = i;
      }
      if(j == 3){
        end = i;
        flag = 0;
      }
    }
    i++;
  }

  buf[end] = '\0';
  buf += start;
  return buf;
}
char* get_gcc_version(char* _buf){
  FILE* fp = fopen("/proc/version", "r");
  char* buf = _buf;
  int start = 0; 
  int end = 0;
  int i = 0;
  int j = 0;
  int flag = 1; 

  fgets(buf, INFO_MAX_LEN, fp);
  while(flag){
    if(buf[i] == ' '){
      j++;
      if(j == 6){
        start = i;
      }
      if(j == 7){
        end = i;
        flag = 0;
      }
    }
    i++;
  }

  buf[end] = '\0';
  buf += start;
  return buf;
}
gboolean get_running_info(gpointer data){
  //current time
  time_t cur_time;
  time_t uptime;
  time_t boot_time;
  struct tm *p;
  struct tm *q;
  struct tm *r;
  long int second;
  int h, m, s;
  time(&cur_time);
   
  //uptime
  FILE* fp= fopen("/proc/uptime", "r");
  int i = 0;
  char buf[INFO_MAX_LEN];
  fgets(buf, INFO_MAX_LEN, fp);
  while(buf[i++] != ' ');
  buf[i - 1] = '\0';
  second = atol(buf);
  uptime = (time_t)second;
  
  //boot time
  if(cur_time > uptime){
    boot_time = cur_time - uptime;
  }else{
    boot_time = uptime - cur_time;
  }
  q = localtime(&boot_time);
  h = second / 3600;
  m = (second % 3600) / 60;
  s = second % 60;
	gchar *string_time = g_strdup_printf(\
    "<span  font_desc='12'>boot time: %02d:%02d:%02d\n\nuptime: %02d:%02d:%02d</span>",\
    q->tm_hour, q->tm_min, q->tm_sec, h, m, s);
	gtk_label_set_markup(GTK_LABEL(data), string_time);
  return TRUE;
}
void get_proc_info(GtkListStore* store){

  DIR* dp;
  struct dirent *entry;

  char buf[PROC_MAX_LEN];
  char pid[PROC_MAX_LEN];
  char name[PROC_MAX_LEN];
  char state[PROC_MAX_LEN];
  char ppid[PROC_MAX_LEN];
  char priority[PROC_MAX_LEN];
  char memory[PROC_MAX_LEN];
  char path[512];
  char* result;
  gchar* list[6];
  int i = 1;
  FILE* fp; 
  GtkTreeIter iter;

  dp = opendir("/proc");
  while((entry = readdir(dp)) != NULL){
    i = 1;
    if((entry->d_name)[0] <'0' || (entry->d_name)[0] > '9') continue;
    // printf("%s\n", entry->d_name);
    sprintf(path, "/proc/%s/stat", entry->d_name);
    fp = fopen(path, "r");
    fgets(buf, INFO_MAX_LEN, fp);
    result = strtok(buf," ");
    while(result != NULL ) {
      if(i > 24) break;
      switch(i){
        case 1: 
          strcpy(pid, result);
          break;
        case 2:
          strcpy(name, result);
          break;
        case 3:
          if(!strcmp(result, "S")){
            strcpy(state, "sleeping");
          }else if(!strcmp(result, "I")){
            strcpy(state, "idle");
          }else if(!strcmp(result, "R")){
            strcpy(state, "running");
          }else if(!strcmp(result, "T")){
            strcpy(state, "stopped");
          }else{
            strcpy(state, result);
          }
          break;
        case 8:
          strcpy(ppid, result);
          break;
        case 18:
          strcpy(priority, result);
          break;
        case 24:
          strcpy(memory, result);
          break;
        default:
          break;
      }
      result = strtok(NULL, " ");
      i++;
    }
    i = 0;
    while(name[i++] != ')');
    name[i-1] = '\0';
    // printf("pid:%s\tname:%s\tstate%s\tpriority%s\ttakeup:%s\n",pid,name,state,priority,memory);
    list[0] = g_strdup_printf("%s", pid);
    list[1] = g_strdup_printf("%s", name+1);
    list[2] = g_strdup_printf("%s", state);
    list[3] = g_strdup_printf("%s", ppid);
    list[4] = g_strdup_printf("%s", priority);
    list[5] = g_strdup_printf("%d", atoi(memory)*4);
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, PID_COL, list[0], NAME_COL, list[1], STATE_COL, list[2],\
      PPID_COL, list[3], PRIORITY_COL, list[4], TAKEUP_COL, list[5], -1);
    fclose(fp);
  }
  closedir(dp);
}

void refresh_proc(GtkListStore* store){
  gtk_list_store_clear(store);
  get_proc_info(store);
}

void kill_proc(void){

}

char* get_username_and_hostname(char* _buf){
  char buf1[INFO_MAX_LEN], buf2[INFO_MAX_LEN];
  char* buf = _buf;  
  int i = 0;

  FILE* fp = fopen("/proc/sys/kernel/hostname", "r");
  fgets(buf1, INFO_MAX_LEN, fp);
  while(buf1[i++] != '\n');
  buf1[i - 1] = '\0';
  fclose(fp);

  fp = popen("whoami","r");
  fgets(buf2, INFO_MAX_LEN, fp);
  i = 0;
  while(buf2[i++] != '\n');
  buf2[i - 1] = '\0';
  pclose(fp);  

  sprintf(buf, "%s@%s", buf2, buf1);
  return buf;
}
/*
gboolean cpu_draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data){
  g_timeout_add(1000, cpu_draw, (void*)widget);
  return TRUE;
}

gboolean cpu_draw(gpointer widget){
        cairo_t *cr;
        cr = gdk_cairo_create (widget->window);

        cairo_set_source_rgb (cr, 0.627, 0, 0);
        cairo_select_font_face (cr, "Adobe Heiti Std", CAIRO_FONT_SLANT_NORMAL,
                                CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 24.0);

        cairo_move_to (cr, 10.0, 34.0);
        cairo_show_text (cr, "我是中国人，我爱我的祖国。");

        cairo_destroy (cr);

        return FALSE;
}


}

gboolean ram_draw_callback(GtkWidget* widget){
  g_timeout_add(1000, ram_draw, (void*)widget);
  return TRUE;
}

gboolean ram_draw(gpointer widget){

}
*/

typedef struct CPU_t{
	unsigned int idle;
	unsigned int total;
}CPU;	
int getCpuStat(CPU* cpu){
	FILE *fr = fopen("/proc/stat", "r");
	char name[256];
	unsigned int a, b, c, idle, d, e, f, g, h;
	fscanf(fr, "%s %u %u %u %u %u %u %u %u %u", name, &a, &b, &c, &idle, &d, &e, &f, &g, &h); 
	// printf("%s %u %u %u %u %u %u %u %u %u\n", name, a, b, c, idle, d, e, f, g, h);
	cpu->idle = idle;
	cpu->total = a + b + c + d + e + f + g + h + idle;
}
gfloat calCpu(CPU* a, CPU *b){
	unsigned int dif_total = b->total - a->total;
	unsigned int dif_idle = b->idle - a->idle;
	if(dif_total !=0){
		return (gfloat)(4*(dif_total - dif_idle)/(float)dif_total);
	}else{
		return (gfloat)(0);	
	}
}

gboolean get_cpu_usage(gpointer data){
	CPU cpu_1, cpu_2;
	getCpuStat((CPU*)&cpu_1);
  sleep(1);
	getCpuStat((CPU*)&cpu_2);
	// printf("cpu_1: idle:%u total:%u\n", cpu_1.idle, cpu_1.total);
	// printf("cpu_2: idle:%u total:%u\n", cpu_2.idle, cpu_2.total);
	gfloat res = calCpu((CPU*)&cpu_1, (CPU*)&cpu_2);
  // printf("%f\n", res);
	gchar buf[32];	
	g_snprintf(buf,8,"<span font_desc='12'> %.1f%%</span>",100*res); 
  gtk_label_set_markup(GTK_LABEL(data), buf);
  return TRUE;
}
gboolean cpu_draw_callback(GtkWidget* widget, cairo_t *cr, gpointer data){
  static pos = 500;
  int i = 0;
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;

  context = gtk_widget_get_style_context (widget);

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);

  gtk_render_background(context, cr, 0, 0, width, height);
  cairo_set_source_rgb(cr, 0.55, 0.5, 0.5);
  for(i = 20; i < 200; i+=20){
    cairo_set_line_cap (cr, CAIRO_LINE_CAP_SQUARE);
    cairo_move_to (cr, 0, i);
    cairo_line_to (cr, 600, i);
    cairo_stroke (cr);
  }
  for(i = 20; i < 600; i+=20){
    cairo_set_line_cap (cr, CAIRO_LINE_CAP_SQUARE);
    cairo_move_to (cr, i + pos, 0);
    cairo_line_to (cr, i + pos, 200);
    cairo_stroke (cr);
  }
  pos -= 10;
  if(pos == 0) pos = 500;

 return FALSE;
}


gboolean ram_draw_callback(GtkWidget* widget, cairo_t *cr, gpointer data){
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;

  context = gtk_widget_get_style_context(widget);

  // width = gtk_widget_get_allocated_width (widget);
  // height = gtk_widget_get_allocated_height (widget);
  cairo_set_source_rgb (cr, 0.627, 0, 0);
  cairo_select_font_face (cr, "Adobe Heiti Std", CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size (cr, 24.0);

  cairo_move_to (cr, 10.0, 34.0);
  cairo_show_text (cr, "我是中国人，我爱我的祖国。");

  return FALSE;
}






























