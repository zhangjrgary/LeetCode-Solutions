桶排序和归并排序有那么点点类似，也使用了归并的思想。大致步骤如下：

设置一个定量的数组当作空桶。
Divide - 从待排序数组中取出元素，将元素按照一定的规则塞进对应的桶子去。
对每个非空桶进行排序，通常可在塞元素入桶时进行插入排序。
Conquer - 从非空桶把元素再放回原来的数组中。