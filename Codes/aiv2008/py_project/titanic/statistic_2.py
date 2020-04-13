import pandas as pd
from pandas import DataFrame
import numpy as np
import matplotlib.pyplot as plt


plt.rcParams['font.sans-serif']=['simhei'] #用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False #用来正常显示负号

#显示所有列
pd.set_option('display.max_columns', None)
#显示所有行
pd.set_option('display.max_rows', None)
#设置value的显示长度为100，默认为50
pd.set_option('max_colwidth',5000)
pd.set_option('expand_frame_repr', False)

data_train = pd.read_csv("data/train.csv")

#print(df.describe())


#plt.subplot2grid((2,4),(0,0))
cabin_notnull_survived = data_train.Survived[pd.notnull(data_train.Cabin)].value_counts()
cabin_null_survived = data_train.Survived[pd.isnull(data_train.Cabin)].value_counts()
cabin_df = pd.DataFrame({u"非空": cabin_notnull_survived, u"空值": cabin_null_survived}).transpose()
cabin_df.plot(kind="bar", stacked=True)
plt.title(u"获救情况")
plt.xlabel(u"获救情况")
plt.ylabel(u"人数")

plt.show()

