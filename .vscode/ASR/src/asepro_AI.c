
//1. 初始化部分


// 初始化函数，系统启动时运行一次
void setup() {
    // 初始化串口（用于调试）
    uart_init(9600);
    
    // 初始化语音识别（用于唤醒和停止）
    voice_init();
    voice_add_wakeword("小智同学");      // 唤醒词
    voice_add_command("开始定时", 1001); // 开始倒计时
    voice_add_command("停止定时", 1002); // 停止倒计时
    voice_add_command("还剩几秒", 1003); // 查询剩余时间
    voice_start();
    
    // 播报启动提示
    voice_play("定时器已就绪，可以说开始定时");
}


//2. 主循环部分

// 定时器相关变量
int countdown_value = 60;       // 倒计时初始值（可修改）
int countdown_running = 0;      // 0=停止, 1=运行中
int last_report_second = 60;    // 上次播报时的秒数

void loop() {
    // 处理语音命令
    check_voice_commands();
    
    // 处理倒计时
    if(countdown_running) {
        handle_countdown();
    }
    
    delay(10);  // 小延时
}
//3. 语音命令处理

// 处理语音命令
void check_voice_commands() {
    int cmd = voice_get_command();
    
    switch(cmd) {
        case 1001:  // "开始定时"
            if(!countdown_running) {
                countdown_value = 60;          // 重置为60秒
                countdown_running = 1;
                last_report_second = 60;
                voice_play("开始60秒倒计时");
            } else {
                voice_play("定时器已经在运行");
            }
            break;
            
        case 1002:  // "停止定时"
            if(countdown_running) {
                countdown_running = 0;
                voice_play_int("定时器已停止，当前剩余", countdown_value, "秒");
            } else {
                voice_play("定时器不在运行状态");
            }
            break;
            
        case 1003:  // "还剩几秒"
            if(countdown_running) {
                voice_play_int("当前还剩", countdown_value, "秒");
            } else {
                voice_play_int("定时器已停止，当前", countdown_value, "秒");
            }
            break;
    }
}
//4. 倒计时处理核心

// 倒计时处理
void handle_countdown() {
    static unsigned long last_time = 0;
    
    // 获取当前系统时间（毫秒）
    unsigned long now = millis();
    
    // 每秒执行一次（1000毫秒间隔）
    if(now - last_time >= 1000) {
        last_time = now;
        
        // 倒计时减1
        countdown_value--;
        
        // 检查是否需要播报（使用TTS合成，不占Flash）
        check_report();
        
        // 倒计时结束
        if(countdown_value <= 0) {
            countdown_value = 0;
            countdown_running = 0;
            voice_play("时间到");
        }
    }
}


//5. 智能播报逻辑（关键部分）

// 检查并播报剩余时间
void check_report() {
    // 播报策略：
    // - 每分钟整点播报（60,59...实际是每分钟播一次）
    // - 最后10秒每秒播报
    
    // 每分钟播报一次（当秒数是60,59,58...的实际效果是每分钟的起始点）
    // 这里简单实现：每当剩余秒数是60,50,40,30,20,10时播报
    if(countdown_value % 10 == 0 && countdown_value != last_report_second) {
        // 使用 TTS 合成播报（不占用Flash存储音频）
        voice_play_int("还剩", countdown_value, "秒");
        last_report_second = countdown_value;
    }
    
    // 最后10秒，每秒播报
    if(countdown_value <= 10 && countdown_value > 0) {
        if(countdown_value != last_report_second) {
            voice_play_int("", countdown_value, "");
            last_report_second = countdown_value;
        }
    }
    
    // 播报结束语
    if(countdown_value == 0 && last_report_second != 0) {
        voice_play("时间到");
        last_report_second = 0;
    }
}


//6. TTS 播报辅助函数

// 播报整数（使用TTS合成，不占Flash空间）
void voice_play_int(char* prefix, int value, char* suffix) {
    char buffer[100];
    
    if(strlen(prefix) > 0 && strlen(suffix) > 0) {
        sprintf(buffer, "%s %d %s", prefix, value, suffix);
    }
    else if(strlen(prefix) > 0) {
        sprintf(buffer, "%s %d", prefix, value);
    }
    else if(strlen(suffix) > 0) {
        sprintf(buffer, "%d %s", value, suffix);
    }
    else {
        sprintf(buffer, "%d", value);
    }
    
    // 调用ASRPRO的TTS引擎播报
    voice_play(buffer);
    
    // 同时串口输出调试
    uart_send_string("播报: ");
    uart_send_string(buffer);
    uart_send_string("\r\n");
}

// 获取系统时间（毫秒）- ASRPRO内置函数
unsigned long millis() {
    // ASRPRO 标准库提供此函数
    // 如果不存在，需要自己实现一个定时器计数
    return system_millis;  // 假设有此变量
}


//7. 串口调试函数


// 串口发送字符串（调试用）
void uart_send_string(char* str) {
    while(*str) {
        uart_send_byte(*str++);
    }
}