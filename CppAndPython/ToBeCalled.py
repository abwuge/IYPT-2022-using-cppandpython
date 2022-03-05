def sim(times, high):
    from cmath import pi
    import pybullet as p
    import time
    import pybullet_data
    import random

    physicsClient = p.connect(p.DIRECT)  # 不展示GUI的套件,速度更快
    p.setAdditionalSearchPath(pybullet_data.getDataPath())  # 添加资源路径
    p.setGravity(0, 0, -9.8)  # 设置环境重力加速度
    p.loadURDF("plane.urdf")  # 加载模型，此处是加载蓝白相间的陆地

    ori = []

    for i in range(times):  # 加载模型，此处是加载蓝色圆柱，共加载i*j（即times的平方）次
        print(i)
        for j in range(times):
            locals()['StartPos' + str(i) + str(j)] \
                = [i * 2, j * 2, high]  # 物体的初始位置
            locals()['StartOri' + str(i) + str(j)] = p.getQuaternionFromEuler(
                [random.uniform(-1, 1) * pi, random.uniform(-1, 1) * pi,
                 random.uniform(-1, 1) * pi])  # 物体的初始角度（随机生成）
            locals()['Cylinder' + str(i) + str(j)] = \
                p.loadURDF("../Cylinder.urdf", locals()['StartPos' + str(i) + str(j)],
                           locals()['StartOri' + str(i) + str(j)], useMaximalCoordinates=True)  # 生成对象

    # 五千次交互
    for i in range(5000):
        p.stepSimulation()

    for i in range(times):
        print(i)
        for j in range(times):
            tem, locals()['EndOri' + str(i) + str(j)] = p.getBasePositionAndOrientation(
                locals()['Cylinder' + str(i) + str(j)])  # 获取方向四元数
            ori.append(locals()['EndOri' + str(i) + str(j)])

    return ori

    # 断开与物理引擎连接
    p.disconnect()


# print(sim(2, 0.5))
