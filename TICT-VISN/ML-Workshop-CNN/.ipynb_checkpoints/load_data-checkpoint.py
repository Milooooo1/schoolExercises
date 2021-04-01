from keras.datasets import mnist
import numpy as np
from typing import Tuple

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

def load_train(padding=((0, 0), (0, 0), (0, 3))) -> Tuple[np.ndarray, np.ndarray]:
    """
    Returns training data, X, y. 
    """
    # train_images = mnist.train_images()

    return np.pad(train_images, padding), train_labels

def load_test(padding=((0, 0), (0, 0), (3, 0))) -> Tuple[np.ndarray, np.ndarray]:
    """
    Returns testing data, X, y. 
    """
    # test_images = mnist.test_images()

    return np.pad(test_images, padding), test_labels

def load_example(index=4, paddingL=((0,0), (0, 3)), paddingR=((0,0), (3, 0))):
    """
    Returns one image twice with different paddings
    """
    # example_image = mnist.test_images()[index]
    
    return (np.pad(example_image[index], paddingL), np.pad(example_image[index], paddingR)), test_labels[index]