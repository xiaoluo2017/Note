# Machine_Learning_Note
Notes for Machine Learning class on Coursera

## Supervised Learning
Given a data set and already know what our correct output should look like
regression problem: predict results within a continuous output
classification problem: predict results in a discrete output

### Linear regression
  

### logistic regression
eg. spam classifer for email
```
% Regularized Logistic Regression Cost Function
h = sigmoid(X * theta);
J = 1 / m * sum((-y .* log(h) - (1 - y) .* log(1 - h))) + lambda / (2 * m) * (sum(theta .* theta) - theta(1) * theta(1));
grad = 1 / m * X' * (h - y) + lambda / m * [0; theta(2: end)];
```

### neural networks
```
% The neural network cost function for a two layer
% Part 1: Feedforward the neural network and return the cost in the variable J.
a1 = [ones(m, 1) X];
z2 = a1 * Theta1';
a2 = [ones(m, 1) sigmoid(z2)];
z3 = a2 * Theta2';
a3 = sigmoid(z3);
h = a3;
y = y == [1: num_labels];
J = sum(sum(1 / m * (-y .* log(h) - (1 - y) .* log(1 - h))));

% Part 2: Implement the backpropagation algorithm to compute the gradients Theta1_grad and Theta2_grad.
J = J + lambda / (2 * m) * (sum(sum(Theta1 .* Theta1)) - sum(Theta1(:, 1) .* Theta1(:, 1)) + sum(sum(Theta2 .* Theta2)) - sum(Theta2(:, 1) .* Theta2(:, 1)));

% Part 3: Implement regularization with the cost function and gradients.
delta_3 = a3 - y;
delta_2 = delta_3 * Theta2(:, 2: end) .* sigmoidGradient(z2);
Theta1_grad = Theta1_grad + delta_2' * a1 / m;
Theta2_grad = Theta2_grad + delta_3' * a2 / m;
Theta1_grad(:, 2: end) = Theta1_grad(:, 2: end) + lambda / m * Theta1(:, 2: end);
Theta2_grad(:, 2: end) = Theta2_grad(:, 2: end) + lambda / m * Theta2(:, 2: end);
```

### SVMs

## Unsupervised Learning
Derive structure from data

### K-means

### PCA

### Anomaly detection

## Special applications/special topics
### Recommender systems

### large scale machine learning

## Advice on building a machine learning system
### Bias/variance, regularization
overfit: Reduce the number of features; Regularization

### deciding what to work on next

### evaluation of learning algorithms, learning curves, error analysis, ceiling analysis
