import pandas as pd #数据分析
import numpy as np #科学计算
from pandas import Series,DataFrame
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties #字体管理器

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

data_train = pd.read_csv("data/train.csv")

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

age_df = data_train[['Age']]
    # 乘客分成已知年龄和未知年龄两部分
age_array = age_df[age_df.Age.notnull()].as_matrix()
print("known age is \n",  len(age_array))

#print(type(serise))
#print(type(age_df))
#print(type(age_array))
print("length of age array is", len(age_array))

step = 2/3
age_array.sort(axis=0, kind='quicksort')
print(age_array)
i = 0
age_list = []
print("last element of age array is", age_array[713])
#age_count_list
if len(age_array) > 0:
	print("type of age array 0 is",type(age_array[0]))
	age_list.append(1)
	j = age_array[0] + step
	while j <= age_array[len(age_array)-1]:
		if i >= len(age_array):
			break
		print("value of j is ", j, "value of i is", i)
		if age_array[i] < j:
			age_list[len(age_list)-1] = age_list[len(age_list)-1] + 1
		else:
			j = j + step
			age_list.append(1)
		i = i + 1
	if i < len(age_array):
		age_list[len(age_list)-1] = age_list[len(age_list)-1] + 1
		i = i = 1
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
