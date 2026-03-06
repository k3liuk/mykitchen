好的，我来帮你完善 ASRPRO 端的语音菜单与 Modbus 寄存器联动 的具体代码。基于你之前的架构，ASRPRO 作为 Modbus 从机，通过保持寄存器与 PLC 共享菜单状态。

📁 ASRPRO 端完整代码（天问Block生成的可视化代码 + C语言混合）

1. 初始化部分（系统启动时运行）

```c
// 初始化函数，系统启动时运行一次
void setup() {
    // 初始化串口（用于调试）
    uart_init(9600);
    
    // 初始化 Modbus 从机
    // 从机地址: 0x01, 波特率: 9600, 无校验, 数据位8, 停止位1
    modbus_slave_init(0x01, 9600, 'N', 8, 1);
    
    // 定义保持寄存器数量（20个保持寄存器）
    modbus_define_holding_registers(20);
    
    // 初始化寄存器值
    modbus_write_holding_register(0x0000, 0x01);  // 当前菜单ID，默认为主菜单(1)
    modbus_write_holding_register(0x0001, 0x00);  // 语音播报触发标志
    modbus_write_holding_register(0x0002, 0x00);  // 上次语音指令ID
    modbus_write_holding_register(0x0010, 0x50);  // 音量值（默认80%）
    modbus_write_holding_register(0x0011, 0x80);  // 亮度值（默认128）
    
    // 初始化语音识别
    voice_init();
    
    // 添加唤醒词
    voice_add_wakeword("小智同学");
    
    // 添加命令词（一级菜单）
    voice_add_command("主菜单", 1);      // 命令ID 1
    voice_add_command("音量设置", 2);    // 命令ID 2
    voice_add_command("亮度设置", 3);    // 命令ID 3
    voice_add_command("关于信息", 4);    // 命令ID 4
    voice_add_command("系统设置", 5);    // 命令ID 5
    
    // 添加命令词（二级菜单 - 音量设置）
    voice_add_command("增加音量", 21);    // 命令ID 21
    voice_add_command("减小音量", 22);    // 命令ID 22
    voice_add_command("静音模式", 23);    // 命令ID 23
    
    // 添加命令词（二级菜单 - 亮度设置）
    voice_add_command("调亮屏幕", 31);    // 命令ID 31
    voice_add_command("调暗屏幕", 32);    // 命令ID 32
    
    // 启动语音识别
    voice_start();
    
    // 初始化时播报欢迎语
    voice_play("系统已启动，当前在主菜单");
}
```

2. 主循环部分（持续运行）

```c
void loop() {
    // 1. 处理 Modbus 通信（必须频繁调用）
    modbus_slave_poll();
    
    // 2. 检查 PLC 是否要求语音播报
    check_plc_voice_command();
    
    // 3. 检查语音识别结果
    check_voice_command();
    
    // 4. 检查菜单状态变化并播报
    check_menu_change();
    
    delay(10);  // 小延时，避免过于占用CPU
}
```

3. 检查 PLC 指令（Modbus 写入检测）

```c
// 检查 PLC 是否通过 Modbus 写入了语音播报指令
void check_plc_voice_command() {
    static unsigned char last_voice_trigger = 0;
    
    // 读取 PLC 写入的播报触发标志（寄存器地址 0x0001）
    unsigned char voice_trigger = modbus_read_holding_register(0x0001);
    
    // 如果 PLC 写入了新值
    if(voice_trigger != last_voice_trigger) {
        last_voice_trigger = voice_trigger;
        
        // 根据触发值播报不同内容
        switch(voice_trigger) {
            case 0x01:
                voice_play("欢迎使用系统");
                break;
            case 0x02:
                voice_play("温度正常");
                break;
            case 0x03:
                voice_play("设备启动中");
                break;
            case 0x04:
                voice_play("任务完成");
                break;
            default:
                // 其他值不播报
                break;
        }
        
        // 播报完成后，将触发标志清0（通知 PLC 已处理）
        modbus_write_holding_register(0x0001, 0x00);
    }
}
```

4. 语音命令处理

```c
// 检查并处理语音识别结果
void check_voice_command() {
    // 获取语音识别结果（非阻塞）
    int cmd_id = voice_get_command();
    
    if(cmd_id > 0) {
        // 有新的语音命令
        // 将命令ID写入寄存器，供 PLC 读取
        modbus_write_holding_register(0x0002, (unsigned char)cmd_id);
        
        // 根据命令ID处理
        process_voice_command(cmd_id);
    }
}

// 处理具体的语音命令
void process_voice_command(int cmd_id) {
    switch(cmd_id) {
        // === 一级菜单命令 ===
        case 1:  // "主菜单"
            // 更新菜单ID寄存器
            modbus_write_holding_register(0x0000, 0x01);
            voice_play("进入主菜单");
            break;
            
        case 2:  // "音量设置"
            modbus_write_holding_register(0x0000, 0x02);
            voice_play("进入音量设置");
            break;
            
        case 3:  // "亮度设置"
            modbus_write_holding_register(0x0000, 0x03);
            voice_play("进入亮度设置");
            break;
            
        case 4:  // "关于信息"
            modbus_write_holding_register(0x0000, 0x04);
            voice_play("本系统版本1.0");
            break;
            
        // === 二级菜单命令 - 音量设置 ===
        case 21:  // "增加音量"
            {
                // 读取当前音量
                unsigned char vol = modbus_read_holding_register(0x0010);
                if(vol < 100) {
                    vol += 10;
                    if(vol > 100) vol = 100;
                    modbus_write_holding_register(0x0010, vol);
                    
                    // 播报当前音量
                    voice_play_int("当前音量", vol);
                }
            }
            break;
            
        case 22:  // "减小音量"
            {
                unsigned char vol = modbus_read_holding_register(0x0010);
                if(vol > 0) {
                    vol -= 10;
                    if(vol < 0) vol = 0;
                    modbus_write_holding_register(0x0010, vol);
                    voice_play_int("当前音量", vol);
                }
            }
            break;
            
        case 23:  // "静音模式"
            modbus_write_holding_register(0x0010, 0x00);
            voice_play("已静音");
            break;
            
        // === 二级菜单命令 - 亮度设置 ===
        case 31:  // "调亮屏幕"
            {
                unsigned char bright = modbus_read_holding_register(0x0011);
                if(bright < 255) {
                    bright += 20;
                    if(bright > 255) bright = 255;
                    modbus_write_holding_register(0x0011, bright);
                }
            }
            break;
            
        case 32:  // "调暗屏幕"
            {
                unsigned char bright = modbus_read_holding_register(0x0011);
                if(bright > 0) {
                    bright -= 20;
                    if(bright < 0) bright = 0;
                    modbus_write_holding_register(0x0011, bright);
                }
            }
            break;
            
        default:
            // 未知命令
            break;
    }
}
```

5. 菜单状态变化自动播报

```c
// 检查菜单ID是否变化（可能由 PLC 通过 Modbus 直接修改）
void check_menu_change() {
    static unsigned char last_menu_id = 0;
    
    // 读取当前菜单ID寄存器
    unsigned char current_menu = modbus_read_holding_register(0x0000);
    
    // 如果菜单ID发生变化
    if(current_menu != last_menu_id) {
        last_menu_id = current_menu;
        
        // 根据菜单ID播报对应的提示
        switch(current_menu) {
            case 0x01:
                voice_play("主菜单");
                break;
            case 0x02:
                voice_play("音量设置菜单");
                break;
            case 0x03:
                voice_play("亮度设置菜单");
                break;
            case 0x04:
                voice_play("关于信息");
                break;
            case 0x05:
                voice_play("系统设置菜单");
                break;
            default:
                break;
        }
    }
}
```

6. 辅助函数

```c
// 播报整数（如音量值）
void voice_play_int(char* prefix, int value) {
    char buffer[50];
    sprintf(buffer, "%s %d", prefix, value);
    voice_play(buffer);
}

// 模拟语音播报函数（实际使用时会调用ASRPRO的语音库）
void voice_play(char* text) {
    // 这里调用 ASRPRO 的语音播报 API
    // 例如：asrpro_tts_play(text);
    
    // 同时可以通过串口输出调试信息
    uart_send_string("播报: ");
    uart_send_string(text);
    uart_send_string("\r\n");
}

// 串口发送字符串（调试用）
void uart_send_string(char* str) {
    while(*str) {
        uart_send_byte(*str++);
    }
}
```

📊 Modbus 寄存器映射表

为了方便 PLC 编程，建议整理一份清晰的寄存器映射表：

寄存器地址 名称 读写属性 取值范围 说明
0x0000 当前菜单ID 读写 1-20 PLC可读当前菜单，也可写强制切换菜单
0x0001 语音播报触发 读写 1-10 PLC写入后触发ASRPRO播报对应语音
0x0002 上次语音指令 只读 1-100 PLC可读用户最后一次说的命令
0x0010 音量设置 读写 0-100 系统音量百分比
0x0011 亮度设置 读写 0-255 屏幕亮度值
0x0020 系统状态 只读 0-255 系统运行状态

🎯 使用说明

1. 在天问Block中：将上述 C 代码粘贴到“代码模式”中，或根据逻辑拖拽图形化模块
2. Modbus 从机地址：代码中设为 0x01，可根据需要修改
3. 寄存器数量：当前定义了20个保持寄存器，可根据需要扩展
4. 与 PLC 交互：PLC 可以直接读写这些寄存器，实现双向通信

需要我帮你调整某个具体功能，或者补充 PLC 端的 Modbus 读取代码吗？