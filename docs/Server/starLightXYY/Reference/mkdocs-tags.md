---
tags:
    - mkdocs
    - plugins
---

# tags

[官方文档](https://squidfunk.github.io/mkdocs-material/setup/setting-up-tags/)

给文章打标签：在文章开头加上
```yaml
---
tags:
  - tag1
  - tag2
  - tag3
---
```

自动生成 tag index
```yaml
[TAGS]
```

在 `mkdocs.yml` 中加上
```yaml
plugins:
    - tags:
        tags_file: tags.md
```

可以给写了一半的文档打上 `todo` 标签，以便快速在首页找到并继续编写
