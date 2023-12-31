---
title: For
---

Repeat a block multiple times.

## Keywords:

### **for**

This expression takes a boolean value and repeats the expression's scope
depending on it's value.

#### Syntax:

```mirim
for <BOOLEAN> {}
```

#### Examples:

```mirim
fun main() int {
    for true { }
}
```

```mirim
fun main() int {
    var resume    = true
    var exit_code = 0

    for resume {
        resume = false
        exit_code = exit_code + 1
    }

    return exit_code
}
```

### **for of**

This expression takes an identifier and an iterable and repeats the expression's scope for each element in the iterable.

#### Syntax:

```mirim
for <IDENTIFIER> of <ITERABLE> {}
```

```mirim
for <IDENTIFIER>, <IDENTIFIER> of <ITERABLE> {}
```

#### Examples:

Iterate over lists or sets.

```mirim
fun main() int {
    let elements = [1, 2, 3]
    var sum      = 0

    for element of elements {
        sum = sum + element
    }

    return sum
}
```

Iterate over lists or sets and get the corresponding index.

```mirim
fun main(args string[]) int {
    var args_count = 0

    for idx, _ of args {
        args_count = idx + 1
    }

    return args_count
}
```

Iterate over maps.

```mirim
fun main() int {
    let language_ranking = [
            "Swift": 6,
            "Go":    9,
            "Rust":  5,
            "Zig":   8,
        ]

    var point_sum = 0

    for _, points of language_ranking {
        point_sum = point_sum + points
    }

    return point_sum
}
```

### **break**

This keyword terminates the execution of a loop.

#### Syntax:

```mirim
for <IDENTIFIER> of <ITERABLE> {
    break
}
```

```mirim
for <IDENTIFIER>, <IDENTIFIER> of <ITERABLE> {
    break
}
```

#### Examples:

```mirim
fun main(args string[]) int {
    var args_until_foo = 0

    for idx, arg of args {
        if arg == "foo" {
            args_until_foo = idx + 1
            break
        }
    }

    return args_until_foo
}
```

### **continue**

This keyword skips one cycle of a loop.

#### Syntax:

```mirim
for <IDENTIFIER> of <ITERABLE> {
    continue
}
```

```mirim
for <IDENTIFIER>, <IDENTIFIER> of <ITERABLE> {
    continue
}
```

#### Examples:

```mirim
fun main(args string[]) int {
    var args_count_without_foo = 0

    for _, arg of args {
        if arg == "foo" {
            continue
        }

        args_count_without_foo = args_count_without_foo + 1
    }

    return args_count_without_foo
}
```
