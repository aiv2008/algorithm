from sklearn.ensemble import RandomForestRegressor
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif']=['simhei'] #用来正常显示中文标签
plt.rcParams['axes.unicode_minus']=False #用来正常显示负号

#fig=plt.figure()
#fig.set(alpha=0.2)


#显示所有列
pd.set_option('display.max_columns', None)
#显示所有行
pd.set_option('display.max_rows', None)
#设置value的显示长度为100，默认为50
pd.set_option('max_colwidth',5000)
pd.set_option('expand_frame_repr', False)


def set_missing_ages(df): 
	age_df = df[['Age','Fare', 'Parch', 'SibSp', 'Pclass']]
	#print(age_df)
	#print(type(age_df))
	#age_notnull = age_df[age_df.Age.notnull()].values()
	age_notnull = np.mat(age_df[age_df.Age.notnull()])
	age_null = np.mat(age_df[age_df.Age.isnull()])
	#print(age_notnull[:, 0])
	#print(type(age_null))
	y = age_notnull[:, 0]
	X = age_notnull[:, 1:]
	


if __name__ == "__main__":
	data_train = pd.read_csv("data/train.csv");
	set_missing_ages(data_train)
