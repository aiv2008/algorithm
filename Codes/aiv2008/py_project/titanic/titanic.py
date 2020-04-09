import pandas as pd #数据分析
import numpy as np #科学计算
from pandas import Series,DataFrame
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties #字体管理器

#设置汉字格式
font = FontProperties(fname=r"/usr/lib/python3/dist-packages/matplotlib/program_font/simhei.ttf", size=15)

#plt.rcParams['font.sans-serif']=['simhei'] #用来正常显示中文标签
#plt.rcParams['axes.unicode_minus']=False #用来正常显示负号

#fig=plt.figure()
#fig.set(alpha=0.2)


#显示所有列
pd.set_option('display.max_columns', None)
#显示所有行
pd.set_option('display.max_rows', None)
#设置value的显示长度为100，默认为50
pd.set_option('max_colwidth',5000)
pd.set_option('expand_frame_repr', False)

data_train = pd.read_csv("data/train.csv")
print(data_train.describe())

plt.subplot2grid((2,4),(0,0))             # 在一张大图里分列几个小图
data_train.Survived.value_counts().plot(kind='bar')# 柱状图 
plt.title(u"获救情况 (1为获救)", fontproperties=font) # 标题
plt.ylabel(u"人数", fontproperties=font) 

plt.subplot2grid((2,4),(0,1))
data_train.Pclass.value_counts().plot(kind='bar')
plt.title(u"等级 1最高", fontproperties=font)
plt.ylabel(u"人数", fontproperties=font)

'''
plt.subplot2grid((2,3),(0,2))
plt.scatter(data_train.Survived, data_train.Age)
plt.title(u"获救情况（1为获救)", fontproperties=font)
plt.ylabel(u"年龄分布", fontproperties=font)

plt.subplot2grid((2,3),(1,0))
plt.scatter(data_train.Pclass, data_train.Age)
plt.title(u"等级为1 的年龄分布", fontproperties=font)
plt.ylabel(u"人数", fontproperties=font)
'''

plt.subplot2grid((2,4),(0,2), colspan=2)
data_train.Age[data_train.Survived==1].plot(kind='kde')
data_train.Age[data_train.Survived==0].plot(kind='kde')
plt.title(u"获救情况年龄分布（1 获救）", fontproperties=font)
plt.xlabel(u"年龄", fontproperties=font)
plt.ylabel(u"密度", fontproperties=font)
plt.legend((u"获救", u"死亡"),loc="best")


plt.subplot2grid((2,4),(1,0), colspan=2)
data_train.Age[data_train.Pclass==1].plot(kind='kde')
data_train.Age[data_train.Pclass==2].plot(kind='kde')
data_train.Age[data_train.Pclass==3].plot(kind='kde')
plt.title(u"乘客等级分布情况", fontproperties=font)
plt.xlabel(u"年龄", fontproperties=font)
plt.ylabel(u"密度", fontproperties=font)
plt.legend((u"头等", u"二等", u"三等"),loc="best")


plt.subplot2grid((2,4),(1,2))
data_train.Embarked.value_counts().plot(kind="bar")
plt.title(u"登陆码头分布情况", fontproperties=font)
plt.ylabel(u"人数", fontproperties=font)

plt.subplot2grid((2,4),(1,3))
survived_0 = data_train.Pclass[data_train.Survived==0].value_counts()
survived_1 = data_train.Pclass[data_train.Survived==1].value_counts()
df=pd.DataFrame({u"死亡": survived_0, u"存活": survived_1})
df.plot(kind="bar", stacked=True)
plt.title(u"乘客等级获救分布情况", fontproperties=font)
plt.xlabel(u"等级",  fontproperties=font)
plt.ylabel(u"获救情况（1 获救）",  fontproperties=font)




plt.show() 
