#include<gtk/gtk.h>
#include<time.h>
#include<unistd.h>
#include<stdio.h>
gboolean settime(gpointer data){
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep);
	gchar *string_time = g_strdup_printf("<span foreground='red' font_desc='16'>%04d-%2d-%2d %02d:%02d:%02d</span>", (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
	gtk_label_set_markup(GTK_LABEL(data), string_time);
	return TRUE;	
}

int showTime(){
	gtk_init(NULL, NULL);
	// 创建窗口、标签、按钮
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *label = gtk_label_new(NULL);
	// 设置窗口大小、位置
	gtk_widget_set_size_request(window, 500, 400);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
//	gtk_widget_set_uposition(GTK_WINDOW(window), 300, 200);
	// 创建组装盒，并将标签和按钮放进去
	GtkWidget *box = gtk_vbox_new(FALSE, 10);
	gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 30);
	//  设置窗口标题
	gtk_window_set_title(GTK_WINDOW(window), "Time");
	//  绑定关闭信号
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//  将组装盒放入窗口 
	gtk_container_add(GTK_CONTAINER(window), box);
	//  实时显示时间
	gint s = g_timeout_add(1000, settime, (void*)label);
	//  显示所有内容
	gtk_widget_show_all(window);
	gtk_main();

}

typedef struct CPU_t{
	unsigned int idle;
	unsigned int total;
}CPU;	
int getCpuStat(CPU* cpu){
	FILE *fr = fopen("/proc/stat", "r");
	char name[256];
	unsigned int a, b, c, idle, d, e, f, g, h;
	fscanf(fr, "%s %u %u %u %u %u %u %u %u %u", name, &a, &b, &c, &idle, &d, &e, &f, &g, &h); 
//	printf("%s %u %u %u %u %u %u %u %u %u\n", name, a, b, c, idle, d, e, f, g, h); 
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

gboolean setcpu(gpointer data){
	CPU cpu_1, cpu_2;
	getCpuStat((CPU*)&cpu_1);
	sleep(1);
	getCpuStat((CPU*)&cpu_2);
//	printf("cpu_1: idle:%u total:%u\n", cpu_1.idle, cpu_1.total);
//	printf("cpu_2: idle:%u total:%u\n", cpu_2.idle, cpu_2.total);
	gfloat res = calCpu((CPU*)&cpu_1, (CPU*)&cpu_2);
//	printf("%f\n", res);
	gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), res);
	gchar buf[8];	
	g_snprintf(buf,8,"%.1f%%",100*res); 
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(data), buf);		
}

int showCPU(){
	gtk_init(NULL, NULL);
	// 创建窗口、标签、按钮
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *progress = gtk_progress_bar_new();
	GtkWidget *label = gtk_label_new("CPU 利用率");
	GtkWidget *fixed = gtk_fixed_new();
	// 设置窗口大小、位置
//	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);	
	gtk_widget_set_size_request(window, 500, 400);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(progress), GTK_PROGRESS_BOTTOM_TO_TOP);
//	gtk_widget_set_uposition(GTK_WINDOW(window), 300, 200);
	// 创建组装盒，并将标签和按钮放进去
/*
	GtkWidget *box = gtk_vbox_new(FALSE, 10);
	gtk_box_pack_start(GTK_BOX(box), progress, TRUE, TRUE, 30);
	gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
*/
	
//	gtk_widget_set_size_request(box, 200, 200); gtk_fixed_put(GTK_FIXED(fixed), progress, 230, 30);
	gtk_fixed_put(GTK_FIXED(fixed), progress, 230, 40);
	gtk_widget_set_size_request(progress, 40, 250);
	gtk_fixed_put(GTK_FIXED(fixed), label, 200, 290);
	gtk_widget_set_size_request(label, 100, 40);
	//  设置窗口标题
	gtk_window_set_title(GTK_WINDOW(window), "CPU");
	//  绑定关闭信号
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//  将组装盒放入窗口 
//	gtk_container_add(GTK_CONTAINER(window), box);
	gtk_container_add(GTK_CONTAINER(window), fixed);
	//  实时显示CPU利用率
	gint s = g_timeout_add(2000, setcpu, (void*)progress);
	//  显示所有内容
	gtk_widget_show_all(window);
	gtk_main();
	

}
gboolean setsum(gpointer data){
	static int i = 0;
	static int sum = 0; 
	if(i == 1000){
		return TRUE;
	}
	i++;
	sum += i;
	gchar buf[100];
	g_snprintf(buf, 100, "<span foreground='blue' font_desc='20'>%d</span>", sum);
	gtk_label_set_markup(GTK_LABEL(data), buf);
	return TRUE;	
}
int showSum(){
	gtk_init(NULL, NULL);
	// 创建窗口、标签、按钮
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *label = gtk_label_new(NULL);
	GtkWidget *fixed = gtk_fixed_new();
	// 设置窗口大小、位置、标题
	gtk_widget_set_size_request(window, 500, 400);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_NONE);
	gtk_window_set_title(GTK_WINDOW(window), "Summing");
	// 设置标签位置、大小
	gtk_fixed_put(GTK_FIXED(fixed), label, 180, 180);
	gtk_widget_set_size_request(label, 150, 40);
	//  绑定关闭信号
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	//  将固定容器放入窗口 
	gtk_container_add(GTK_CONTAINER(window), fixed);
	//  实时显示时间
	gint s = g_timeout_add(1000, setsum, (void*)label);
	//  显示所有内容
	gtk_widget_show_all(window);
	gtk_main();

}
int main(int argc, char *argv[]){
	pid_t p1, p2;
	if((p1 = fork()) == 0){
		showTime();
		return 0;
			
	}else if((p2 = fork()) == 0){
		showCPU();
		return 0;
	}else{
		showSum();
		wait(&p1);
		wait(&p2);
		return 0;
	}
}
