import pandas as pd #数据分析
import numpy as np #科学计算
from pandas import Series,DataFrame
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties #字体管理器
import math

#设置汉字格式
#font = FontProperties(fname=r"/usr/lib/python3/dist-packages/matplotlib/program_font/simhei.ttf", size=15)

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


def get_hd(class_list):
	if len(class_list) <= 0:
		return None
	if isinstance(class_list, list) == False:
		return None
	total = 0.0
	for obj in class_list:
		total = total + obj
	if total == 0.0:
		return 0.0
	hd_val = 0.0
	for obj in class_list:
		lg_pr = 0 if obj == 0 else math.log(obj/total, 2)
		hd_val = hd_val + (obj / total) * lg_pr
	return -hd_val
	#return total

#calculate the  entropy of the data frame, the feature of X is 'Fare', 'Parch', 'SibSp', 'Pclass', the output feature is 'Age'
def cal_entropy(df):
	#df.sort_values(by='Age', ascending=False)
	#print(df)
	known_age_df = df[df.Age.notnull()].sort_values(by='Age', kind='quicksort', ascending=True)
	#print("type of known age is", type(known_age_df))
	#return the numpy array with the condition of age which is not null
	known_age_array = df[df.Age.notnull()].to_numpy()
	#return the numpy array with the condition of age which is  null
	unknown_age_array = df[df.Age.isnull()].to_numpy()
	#print(known_age_df.info())
	#print(known_age_df.describe())
	print(known_age_df)

#print(data_train.describe())

'''
data_train.Age.plot(kind="kde")
plt.title(u"年龄分布")
plt.xlabel(u"年龄")
plt.ylabel(u"密度")
'''
#plt.show()

#serise = data_train.Age
#age_df = data_train[['Age']]
#age_array = data_train[['Age']].Age.notnull().as_matrix()

def get_cls_list(data_train, pty):

	#age_df = data_train[['Age']]
	age_df = data_train[[pty]]
	    # 乘客分成已知年龄和未知年龄两部分
	#age_array = age_df[age_df.Age.notnull()].as_matrix()
	age_array = age_df[age_df[pty].notnull()].as_matrix()
	print("known age is \n",  len(age_array))

	#print(type(serise))
	#print(type(age_df))
	#print(type(age_array))
	print("length of age array is", len(age_array))

	step = 2/3
	age_array.sort(axis=0, kind='quicksort')
	#print(age_array)
	i = 0
	age_list = []
	print("last element of age array is", age_array[713])
	#age_count_list
	if len(age_array) > 0:
		print("type of age array 0 is",type(age_array[0]))
		age_list.append(0)
		j = age_array[0] + step
		while j <= age_array[len(age_array)-1]:
			if i >= len(age_array):
				break
			print("value of j is ", j, "value of age_array is", age_array[i])
			if age_array[i] < j:
				age_list[len(age_list)-1] = age_list[len(age_list)-1] + 1
				i = i + 1
			else:
				j = j + step
				while age_array[i] > j:
					j = j + step
				age_list.append(0)
			#i = i + 1
		if i < len(age_array):
			age_list[len(age_list)-1] = age_list[len(age_list)-1] + 1
			i = i + 1
		print("length of age list is:\n")
		print(len(age_list))
		print("age list is:\n")
		print(age_list)

		i=0
		total_count=0
		for i in range(len(age_list)):
			total_count = total_count + age_list[i]
		print("total count is:\n")
		print(total_count)
	else:
		print("age list is null")
	return age_list


		
if __name__ == '__main__':
	data_train = pd.read_csv("data/train.csv")
	age_df = data_train[['Age','Pclass', 'SibSp','Parch','Fare']]
	cal_entropy(age_df)
	#print(data_train.describe())
	#result_list = get_cls_list(data_train, 'Age')
	#hd_val = get_hd(result_list)
	#print("hd_val=", hd_val)
	


