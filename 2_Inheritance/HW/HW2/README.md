## Question
Fix the following program, make it OO.
```java
import java.util.ArrayList;

public class EmployeeCensus extends ArrayList<Employee> {
	public void addEmployee(Employee employee) {
		add(employee);
	}

	public void removeEmployee(Employee employee) {
		remove(employee);
	}
}

class Employee {
	// not important
}
```

## Ans

實現物件導向的規則可以參考[筆記](../../0_Inheritance/README.md)
1. is `<sub class>` a `<base class>`
    > 繼承有遞移性(transitive)，以下例子而言，也需要滿足 `An american is a human?`
    > ![alt text](image.png)
1. is `<sub class>` specialized than the `base class`? e.g. have other methods, members
2. `<base class>` is not necessary `<sub class>`
3. `<sub class>` needs all member/method defined in `<base class>`

目前的程式不符合第一條件，因為在語意上是 `EmployeeCensus has a list of Employee` 而不是 `EmployeeCensus is a list of Employee`， `EmployeeCensus` 不應該是 `ArrayList<Employee>`。

這邊的改法是使用 Composition 而不是 inheritance


```java
import java.util.ArrayList;

public class EmployeeCensus extends Employee {
	private ArrayList<Employee> employees = new ArrayList<>();

    public EmployeeCensus() {} // constructor

    public void addEmployee(Employee employee) {
		employees.add(employee);
	}

	public void removeEmployee(Employee employee) {
		employees.remove(employee);
	}
}

class Employee {
	// not important
}
```
