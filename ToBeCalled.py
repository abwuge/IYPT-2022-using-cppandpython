def sim(times, high):
    from cmath import pi
    import pybullet as p
    import time
    import pybullet_data
    import random

    # p.connect(p.GUI)
    p.connect(p.DIRECT)  # 不展示GUI的套件,速度更快
    # p.configureDebugVisualizer(p.COV_ENABLE_RENDERING, 0)
    p.configureDebugVisualizer(p.COV_ENABLE_GUI, 0)
    # p.configureDebugVisualizer(p.COV_ENABLE_TINY_RENDERER, 0)
    p.setAdditionalSearchPath(pybullet_data.getDataPath())  # 添加资源路径
    p.setGravity(0, 0, -9.8)  # 设置环境重力加速度
    p.loadURDF("plane.urdf")  # 加载模型，此处是加载蓝白相间的陆地
    p.resetDebugVisualizerCamera(cameraDistance=5, cameraYaw=0, cameraPitch=269, cameraTargetPosition=[0, 0, 0])

    ori = []

    print("对象生成中...")
    for i in range(times):  # 加载模型，此处是加载蓝色圆柱，共加载i*j（即times的平方）次
        for j in range(times):
            locals()['StartPos' + str(i) + str(j)] \
                = [(random.uniform(-1, 1) * 5), (random.uniform(-1, 1) * 5), high]  # 物体的初始位置
            locals()['StartOri' + str(i) + str(j)] = p.getQuaternionFromEuler(
                [random.uniform(-1, 1) * pi, random.uniform(-1, 1) * pi,
                 random.uniform(-1, 1) * pi])  # 物体的初始角度（随机生成）
            locals()['Cylinder' + str(i) + str(j)] = \
                p.loadURDF("../../Cylinder.urdf", locals()['StartPos' + str(i) + str(j)],
                           locals()['StartOri' + str(i) + str(j)], useMaximalCoordinates=True)  # 生成对象
            p.changeDynamics(locals()['Cylinder' + str(i) + str(j)], -1, restitution=0, lateralFriction=0.35,
                             spinningFriction=0.35, rollingFriction=0.0001)
            p.resetBaseVelocity(locals()['Cylinder' + str(i) + str(j)],
                                [(random.uniform(-1, 1) * 3), (random.uniform(-1, 1) * 3), (random.uniform(-1, 1) * 3)],
                                [random.uniform(-1, 1) * pi, random.uniform(-1, 1) * pi, random.uniform(-1, 1) * pi])
            p.setCollisionFilterGroupMask(locals()['Cylinder' + str(i) + str(j)], -1,
                                          collisionFilterGroup=-1, collisionFilterMask=0)
    print("对象生成完成")

    # 五千次交互
    for i in range(1000):
        p.stepSimulation()
        if i % 100 == 0:
            print(i/100)
        # time.sleep(1/240)

    print("读取数据中...")
    for i in range(times):
        for j in range(times):
            tem, locals()['EndOri' + str(i) + str(j)] = p.getBasePositionAndOrientation(
                locals()['Cylinder' + str(i) + str(j)])  # 获取方向四元数
            ori.append(locals()['EndOri' + str(i) + str(j)])
    print("读取数据完成")

    p.disconnect()  # 断开与物理引擎连接

    return ori


# print(sim(5, 1))
