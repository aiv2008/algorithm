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

#calculate the  entropy of the data frame, the feature of X is 'Fare', 'Parch', 'SibSp', 'Pclass', the output feature is 'Age', the order is
#'Age','Pclass', 'SibSp','Parch','Fare'
def cal_entropy(df):
	known_age_df = df[df.Age.notnull()].sort_values(by="Age", kind="quicksort", ascending=True)
	known_age_array = df[df.Age.notnull()].to_numpy()
	unknown_age_array = df[df.Age.isnull()].to_numpy()
	sorted_array = known_age_array[known_age_array[:,4].argsort()]


	#显示所有列
	pd.set_option('display.max_columns', None)
	#显示所有行
	pd.set_option('display.max_rows', None)
	#设置value的显示长度为100，默认为50
	pd.set_option('max_colwidth',5000)
	pd.set_option('expand_frame_repr', False)
 
	print(sorted_array)	
	#print(known_age_df)

def get_cls_list(np_array, step):
	i = 0
	result_list = []
	#print("last element of age array is", np_array[713])
	#age_count_list
	if len(np_array) > 0:
		print("type of age array 0 is",type(np_array[0]))
		result_list.append(0)
		j = np_array[0] + step
		while j <= np_array[len(np_array)-1]:
			if i >= len(np_array):
				break
			print("value of j is ", j, "value of np_array is", np_array[i])
			if np_array[i] < j:
				result_list[len(result_list)-1] = result_list[len(result_list)-1] + 1
				i = i + 1
			else:
				j = j + step
				while np_array[i] > j:
					j = j + step
				result_list.append(0)
			#i = i + 1
		if i < len(np_array):
			result_list[len(result_list)-1] = result_list[len(result_list)-1] + 1
			i = i + 1
		print("length of age list is:\n")
		print(len(result_list))
		print("age list is:\n")
		print(result_list)

		i=0
		total_count=0
		for i in range(len(result_list)):
			total_count = total_count + result_list[i]
		print("total count is:\n")
		print(total_count)
	else:
		print("age list is null")
	return result_list

		
if __name__ == "__main__":
	data_train = pd.read_csv("data/train.csv")
	#显示所有列
	pd.set_option('display.max_columns', None)
	#显示所有行
	pd.set_option('display.max_rows', None)
	#设置value的显示长度为100，默认为50
	pd.set_option('max_colwidth',5000)
	pd.set_option('expand_frame_repr', False)
	tp_array = ["Age", "Pclass", "SibSp", "Parch", "Fare"]
#	dtype = np.dtype([("Age","S10"), ("Pclass","S10"), ("SibSp","S10"), ("Parch","S10"), ("Fare","S10")])
#	age_df = data_train[['Age','Pclass', 'SibSp','Parch','Fare']]
	age_df = data_train[tp_array]
	cal_entropy(age_df)
	#print(data_train.describe())
	#result_list = get_cls_list(data_train, 'Age')
	#hd_val = get_hd(result_list)
	#print("hd_val=", hd_val)
	


