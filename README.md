# Chase — UE5 第一人称追逃收集原型

> 第一人称收集 + 敌人追捕的小游戏原型:收集物计数进 GameState,敌人靠 AI 感知与行为树追你并周期性造成伤害
> (玩家受击有短暂无敌帧),收集满才能进通关房间。**C++ 承担玩法逻辑,蓝图负责资源与表现。**

## 简介

| | |
|---|---|
| **项目类型** | 第一人称追逃 / 收集小游戏(单机原型) |
| **引擎版本** | Unreal Engine 5.3 |
| **实现方式** | C++(玩法逻辑)+ 蓝图(资源与表现)混合 |
| **C++ 规模** | 30 个头文件 / 源文件(15 个类) |
| **用到的引擎系统** | 增强输入(Enhanced Input)、GameState + 动态多播委托、接口(伤害)、球体碰撞重叠、AI 感知(Sight)+ 行为树 + 黑板 + 自定义 BTTask、UMG(HUD / 死亡 / 通关面板) |
| **入口关卡** | `/Game/MyselfContent/Maps/TestMap`,默认 GameMode 为 `GM_ChaseGameMode` |

## 玩法流程

```
收集物(球体重叠)──→ 加分数 + 剩余数 -1 ──→ GameState 广播(新分数, 剩余数) ──→ HUD / 面板刷新
敌人 AI:感知到玩家 ──→ 写入黑板 ──→ 行为树决策(追人 / 巡逻)──→ 攻击区重叠 ──→ 周期性扣血
玩家受击 ──→ 无敌帧(计时器)──→ 血量归零 ──→ 死亡面板(重开 / 退出)
收集满 + 进入通关房间(通关房间订阅分数,没满不给过)──→ 通关面板
```

## 实现要点(结构)

- **分数与剩余数收在 GameState**:收集物在 BeginPlay 时把总数登记到 GameState,拾取时扣减并广播 —— UI 不主动查数据,只订阅广播,数据和界面彻底分开。
- **一个动态多播委托驱动所有界面**:`(新分数, 剩余数)` 委托被游玩 HUD、死亡面板同时订阅,以后加新界面不用动游戏逻辑。
- **伤害走接口**:玩家实现伤害接口,敌人只调用接口、不认具体角色类型 —— 以后让别的单位也能被打,不用改敌人代码。
- **无敌帧做在受击处理里**:受击先判状态、再用计时器恢复,避免连续重叠帧把血一次扣光。
- **敌人 AI 分三层**:AI 控制器管感知(视线配置)与黑板写入、行为树管决策、自定义 BTTask 管「取玩家位置」「找巡逻点」这类原子动作 —— 决策与实现分开,改行为不用改控制器。
- **HUD 统一创建面板**:HUD 类持有三个 UMG 子类(游玩 HUD / 死亡面板 / 通关面板),按游戏状态创建与显示;UMG 内部用 BindWidget 拿控件,不硬编码控件路径。
- **通关要有条件**:通关房间订阅分数委托,收集没满就不给过 —— 用数据条件驱动胜负,而不是「碰到就赢」。

## 目录结构

```
Source/Chase/                        C++ 源码
  ChasePlayerCharacter.*             玩家(增强输入、实现伤害接口、无敌帧、死亡处理)
  ChasePlayerController.*            玩家控制器
  ChaseGameState.*                   分数 / 剩余收集物 + 分数变化委托
  ChaseCollectible.*                 收集物(登记总数、重叠拾取、加分)
  ChaseEnemyCharacter.*              敌人(攻击区重叠、攻击间隔与冷却)
  ChaseEnemyAIController.*           AI 控制器(视线感知、黑板写入、队伍号)
  HealthInterface.*                  伤害接口
  EndRoom.*                          通关房间(订阅分数,满足条件才通关)
  ChasePlayHUD.*                     HUD(创建游玩 HUD / 死亡面板 / 通关面板)
  ChasePlayHUDUserWidget.*           游玩 HUD 控件(显示剩余收集物)
  DeadPanelUserWidget.*              死亡面板(最终分数、重开 / 退出)
  ClearGameUserWidget.*              通关面板(重开 / 退出)
  TN_FindPlayerLocation.*            行为树任务:取玩家位置写黑板
  TN_WalkAround.*                    行为树任务:巡逻点写黑板
Content/MyselfContent/
  Maps/TestMap.umap                  关卡(默认关卡)
  GameBase/                          GM_Chase、GM_ChaseGameMode、GS_ChaseGameState、玩家控制器蓝图
  Blueprint/                         玩家 / 收集物 / 敌人 / 通关房间蓝图
  UI/                                游玩 HUD、死亡面板、通关面板、剩余收集物控件
  Input/                             增强输入资产(移动 / 视角 / 输入映射上下文)
  Material/                          收集物材质
Config/                              项目与输入配置
```

## 如何打开

1. 安装 **Unreal Engine 5.3** 与 **Visual Studio 2022**(需含「使用 C++ 的游戏开发」工作负载)。
2. `git clone` 本仓库,右键 `Chase.uproject` → **Generate Visual Studio project files** → 编译
   (或直接双击 `.uproject`,提示编译模块时选 Yes)。
3. 本仓库不含 UE 官方模板资源(StarterContent / 官方人形等,共约 600 MB):用 UE 新建一个 **First Person C++ 模板**
   工程,把它的 `Content/StarterContent`、`Content/Characters` 补进本项目 `Content/` 下即可完整显示。
4. 入口关卡 `/Game/MyselfContent/Maps/TestMap`。

## 说明

- 仓库只包含本人产出的 C++ 源码、蓝图与资源;UE 官方模板资源未包含(见「如何打开」第 3 步)。
- 项目仍在开发中:玩法闭环(收集 → 计分 → 追捕 → 受伤 → 死亡 / 通关)已通,关卡内容与行为树细节还在推进,仓库会随开发更新。
