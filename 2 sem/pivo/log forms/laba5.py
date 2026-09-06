import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
from sklearn.metrics import r2_score, mean_absolute_error
from sklearn.model_selection import train_test_split

# Генерация данных
np.random.seed(42)
n = 500
distance = np.random.uniform(1, 30, n)
num_orders = np.random.randint(1, 10, n)
traffic = np.random.uniform(0, 1, n)
time = 15 + distance*2 + num_orders*3 + traffic*20 + np.random.normal(0, 3, n)

data = pd.DataFrame(
    {'distance': distance, 'orders': num_orders, 'traffic': traffic, 'time': time})
X_train, X_test, y_train, y_test = train_test_split(
    data[['distance', 'orders', 'traffic']], data['time'], test_size=0.2, random_state=42)
model_simple = LinearRegression()
model_simple.fit(X_train[['distance']], y_train)  # баз вр
y_pred_simple = model_simple.predict(X_test[['distance']])
print(" ОДИНОЧНАЯ ЛИНЕЙНАЯ РЕГРЕССИЯ ")
print(
    f"Уравнение: time = {model_simple.intercept_:.2f} + {model_simple.coef_[0]:.2f} * distance")
print(f"R² = {r2_score(y_test, y_pred_simple):.4f}, MAE = {mean_absolute_error(y_test, y_pred_simple):.2f} мин\n")

model_multiple = LinearRegression()
model_multiple.fit(X_train, y_train)
y_pred_multiple = model_multiple.predict(X_test)
print(" МНОЖЕСТВЕННАЯ ЛИНЕЙНАЯ РЕГРЕССИЯ ")
print(
    f"Уравнение: time = {model_multiple.intercept_:.2f} + {model_multiple.coef_[0]:.2f}*distance + {model_multiple.coef_[1]:.2f}*orders + {model_multiple.coef_[2]:.2f}*traffic")
print(f"R² = {r2_score(y_test, y_pred_multiple):.4f}, MAE = {mean_absolute_error(y_test, y_pred_multiple):.2f} мин\n")
# оч 3 заг 20
importance = pd.DataFrame(
    {'Признак': ['distance', 'orders', 'traffic'], 'Коэффициент': model_multiple.coef_})
print(" ВЛИЯНИЕ ПРИЗНАКОВ \n", importance.to_string(index=False))
print(
    f"\nВывод: Улучшение R² на {(r2_score(y_test, y_pred_multiple) - r2_score(y_test, y_pred_simple)):.4f} при использовании множественной регрессии")

fig, axes = plt.subplots(1, 3, figsize=(15, 4))
axes[0].scatter(X_test['distance'], y_test, alpha=0.5, label='Факт')
axes[0].scatter(X_test['distance'], y_pred_simple, alpha=0.5, label='Прогноз')
axes[0].set_xlabel('Расстояние (км)')
axes[0].set_ylabel('Время (мин)')
axes[0].set_title('Одиночная регрессия')
axes[0].legend()
axes[1].scatter(y_test, y_pred_multiple, alpha=0.5)
axes[1].plot([y_test.min(), y_test.max()], [
             y_test.min(), y_test.max()], 'r--', lw=2)
axes[1].set_xlabel('Фактическое время')
axes[1].set_ylabel('Прогноз')
axes[1].set_title('Множественная регрессия')
axes[2].barh(importance['Признак'], importance['Коэффициент'])
axes[2].set_xlabel('Коэффициент')
axes[2].set_title('Влияние признаков')
plt.tight_layout()
plt.savefig('/tmp/regression_analysis.png', dpi=150)
plt.show()
