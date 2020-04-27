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
#	print(age_df[age_df.Age.notnull()])
#	print(age_df[age_df.Age.isnull()])
	age_notnull = age_df[age_df.Age.notnull()].as_matrix()
	age_null = age_df[age_df.Age.isnull()].as_matrix()
	X = age_notnull[:, 1:]
	y = age_notnull[:, 0]
	#print(y)
	rfr = RandomForestRegressor( n_estimators=2000, n_jobs=-1)
	rfr.fit(X,y)
	predictedAges = rfr.predict(age_null[:, 1:])
	age_df.loc[age_df.Age.isnull(), "Age"] = predictedAges
	print(age_df.sort_values(by="Age", ascending=True))	
'''
	print(predictedAges)
	print(y.shape)
	print(np.sort(y, kind="quicksort"))
	print(predictedAges.shape)
	print(np.sort(predictedAges, kind="quicksort"))
	print(df.describe())
	print(df.info())
'''

if __name__ == "__main__":
	data_train = pd.read_csv("data/train.csv");
	set_missing_ages(data_train)
