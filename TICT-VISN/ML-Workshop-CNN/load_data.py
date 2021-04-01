from keras.datasets import mnist
import numpy as np
from typing import Tuple

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

def load_train(padding=((0, 0), (0, 0), (0, 3))) -> Tuple[np.ndarray, np.ndarray]:
    return np.pad(train_images, padding), train_labels

def load_test(padding=((0, 0), (0, 0), (3, 0))) -> Tuple[np.ndarray, np.ndarray]:

    return np.pad(test_images, padding), test_labels

def load_example(index=4, paddingL=((0,0), (0, 3)), paddingR=((0,0), (3, 0))):
    example_image = test_images[index] #Test    
    return (np.pad(example_image, paddingL), np.pad(example_image, paddingR)), mnist.test_labels[index]