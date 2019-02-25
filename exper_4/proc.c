#include <gtk/gtk.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define INFO_MAX_LEN 512
#define PROC_MAX_LEN 128 

gboolean get_cur_time(gpointer data);

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
void get_proc_info(GtkWidget* clist);
void refresh_proc(GtkWidget* clist);
void kill_proc(void);


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
  GtkWidget* clist;
  GtkWidget* button_1;
  GtkWidget* button_2;

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
 
  vbox = gtk_vbox_new(FALSE, 5);
  // gtk_widget_set_size_request(vbox,)
  gtk_container_add(GTK_CONTAINER(window), vbox);



  label_time = gtk_label_new(NULL);
  // gtk_widget_set_size_request(label_time, 100, 20);
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
  gtk_container_set_border_width(GTK_CONTAINER(notebook), 20);
  



  //*****************第一个标签页, 系统信息
  vbox = gtk_vbox_new(FALSE, 5);

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
  vbox = gtk_vbox_new(FALSE, 5);
  scrolled_window = gtk_scrolled_window_new(NULL, NULL);
  clist = gtk_clist_new(6);
  get_proc_info(clist);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);   
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), (gpointer)clist); 
  gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 5);

  hbox = gtk_hbox_new(FALSE, 10);

  button_1 = gtk_button_new_with_label("Kill");
  gtk_widget_set_size_request(button_1, 100, 35);
  g_signal_connect(GTK_OBJECT(button_1), "clicked",G_CALLBACK (kill_proc), NULL);
  gtk_box_pack_end(GTK_BOX(hbox), button_1, FALSE, FALSE, 10);

  button_2 = gtk_button_new_with_label("Refresh");
  gtk_widget_set_size_request(button_2, 100, 35);
  g_signal_connect_swapped(GTK_OBJECT(button_2), "clicked", G_CALLBACK(refresh_proc), clist);  
  gtk_box_pack_end(GTK_BOX(hbox), button_2, FALSE, FALSE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);

  label = gtk_label_new("Process");
  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), vbox, label);

  //**************************第三个标签页,Performance 
  GtkWidget *frame_4 = gtk_frame_new(NULL);
  label = gtk_label_new("Performance");

  gtk_notebook_append_page(GTK_NOTEBOOK(notebook), frame_4, label);

  // 第四个标签页, About
  vbox = gtk_vbox_new(FALSE, 5);


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
void get_proc_info(GtkWidget* clist){

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


  gtk_clist_set_column_title(GTK_CLIST(clist),0,"PID");
  gtk_clist_set_column_title(GTK_CLIST(clist),1,"Name");
	gtk_clist_set_column_title(GTK_CLIST(clist),2,"State"); 
  gtk_clist_set_column_title(GTK_CLIST(clist),3,"PPID");
	gtk_clist_set_column_title(GTK_CLIST(clist),4,"Priority"); 
	gtk_clist_set_column_title(GTK_CLIST(clist),5,"Takeup"); 
  gtk_clist_set_column_width(GTK_CLIST(clist),0,50);
  gtk_clist_set_column_width(GTK_CLIST(clist),1,150);
  gtk_clist_set_column_width(GTK_CLIST(clist),2,80);
  gtk_clist_set_column_width(GTK_CLIST(clist),3,50);
  gtk_clist_set_column_width(GTK_CLIST(clist),4,100);
  gtk_clist_set_column_width(GTK_CLIST(clist),5,55);
  gtk_clist_column_titles_show(GTK_CLIST(clist)); 
  
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
    gtk_clist_append(GTK_CLIST(clist), list);
    fclose(fp);
  }
  closedir(dp);
}

void refresh_proc(GtkWidget* clist){
  gtk_clist_clear(GTK_CLIST(clist));
  get_proc_info(clist);
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






























