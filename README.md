electronic-measurement-experiment
=================================

A backup of my homework.

今年的实验也实行线上操作（仿真），实验这样要求：设计一个温度测量与控制系统，
用热敏电阻作为传感器（可以用电位器），采用A/D变换，用单片机采集（或者其他CPU
）,用LCD显示用（最好中文显示），控制系统可以用继电器控制电机的正反转，其他的
自由发挥。

Dependent
---------

1.  A LaTex distribution. Such as [texlive].
2.  [njustthesis].
3.  [boxie].

Install
-------

``` {.zsh}
git clone git@github.com:Freed-Wu/electronic-measurement-experiment
cd electronic-measurement-experiment
latexmk -pvc main.tex
```

Q & A
-----

More question see [Issues].

If you don't wanna compile, you can download the complied paper from
[Release]

  [texlive]: https://github.com/TeX-Live/texlive-source
  [njustthesis]: https://github.com/Freed-Wu/njustthesis
  [boxie]: https://github.com/registor/boxiesty
  [Issues]: https://github.com/Freed-Wu/electronic-measurement-experiment/issues
  [Release]: https://github.com/Freed-Wu/electronic-measurement-experiment/releases/

