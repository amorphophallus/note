# Ant Design

[TOC]



## 常用组件和头文件



### Layout



#### 头文件



```js
import { Layout } from 'antd';
const { Header, Footer, Sider, Content } = Layout;
import 'antd/dist/antd.css';
```



#### 常用技巧



```js
// 添加 css
<Layout className="layout">
<Header id="header">
<Content style={{
                margin: 'auto',
                height: '200px'
               }}>
```



```css
/* 常用的 css 参数 */
.layout{
    background-color: white, /* 背景颜色，不能直接在 HTML 中设置 */
    color: black, /* 字体颜色 */
}
```





#### tips



1. 添加 class 时 Layout 和 Content 都可以用 `class='classname'` 但是 Header 只能用 `className='classname'` ，所以就统一用 className 了。
2. css 是要 import 的 xswl



### Radio



#### 基本用法



```javascript
import { Radio } from 'antd'; // 单选

// 布局：radio 嵌套 Space
<Radio.Group onChange={onChange} value={value}>
    <Space direction="vertical">
        <Radio value={1}>Option A</Radio>
    </Space>
</Radio.Group>

// 获取 Radio 的值：onChange 函数默认有一个参数 e.target.value 就是选中的值
const onChange = (e: RadioChangeEvent) => {
    setValue(e.target.value);
};
```







### Checkbox



#### 头文件



```js
import { Checkbox } from 'antd'; // 多选
```



#### 常见用法



1. 多选

首先要搞清楚几个参数的作用

```js
// 单个 Checkbox
// onChange 可以在这个多选框状态改变的时候做一些操作， checked 和 disabled 使得可以通过其他方式修改这个多选框的状态，indeterminate 是半选状态
<Checkbox checked={checked} disabled={disabled} onChange={onChange} indeterminate={indeterminate}>选项内容</Checkbox>

// Checkbox Group
// options 是所有选项内容构成的数组，value 是选中选项的 value 构成的数组
// options 中存储的数据形式是 {label: '选项内容', value: '选项key'， disabled: true/false}，但也可以直接存字符串，默认 label 和 value 相同
// 可以在 css 中用 flex-direction 排版
<Checkbox.Group options={plainOptions} value={checkedList} onChange={onChange} />
    
// Checkbox.Group 的另一种写法，配合 grid 比较容易排版
 <Checkbox.Group>
    <Row>
      <Col span={8}>
        <Checkbox value="A">A</Checkbox>
      </Col>
      <Col span={8}>
        <Checkbox value="B">B</Checkbox>
      </Col>
    </Row>
</Checkbox.Group>

// onChange 函数中 e.target 是状态改变的那个 checkbox
const onChange = (e) => {
    console.log('checked = ', e.target.checked);
};
```



onChange 的逻辑比较怪，在调用 onChange 函数的时候，`e.target.checked` 已经被修改过了，和 `checked={...}` 里面的内容是不一样的。但是 onChange 函数调用结束之后，重新渲染的时候会重新把 `checked` 赋值成 ... 里面的值。



2. Grid 语法



```js
<col></col>
<row></row>
```





#### tips

1. 把同一个系列的所有 Checkbox 放在同一个函数组件里，用一个 `state hook：checked` 数组记录有哪些已经选中了
2. CheckBox 有没有 checked 和 value 数组并不影响其本身相应点击，这两个参数是为了方便导出数据和方便外部控制 Checkbox（**value的作用是强制设置哪几个元素被选中**）
3. value 可以包含 options 中没有的元素
4. 在 `Checkbox.Group` 中设置单个 `Checkbox` 的 `defaultChecked` 是没有用的，需要在 `Checkbox.Group` 中设置 `defaultValue`





### 菜单 Menu



#### 头文件和基本使用



```js
import { Menu } from 'antd';

// 封装成一个函数，生成一个 item
function getItem(label, key, children=null, type=null, icon = null) {
  return {
   	key: key,
    icon: icon,
    children: children,
    label: label,
    type: type,
  };
}

// 把 item 嵌套地放进 items 数组
const items = [
  getItem('Navigation One', 'sub1', [
    getItem('Option 5', '5'),
  ], 'group') // type 设置成 'group' 则目录不会折叠
];

// 渲染 Menu
<Menu
  onClick={onClick}
  style={{ width: 256 }} // 注意要两层括号
  defaultSelectedKeys={['1']} // 默认选中（变色）的目录
  defaultOpenKeys={['sub1']} // 默认展开的目录
  mode="inline" // 不设置 mode 子目录会以下拉栏的形式渲染， inline 之后会在下方展开
  items={items}
/>
```



#### 其他参数



```js
items: type
Menu: mode
Menu: defaultOpenKeys={数组} // 保存一些 key，默认不折叠
```





#### tips

1. **Menu 嵌套**：label 的类型是 React.ReactNode，所以一切可以被渲染的元素都可以作为 label。比如说 Menu 可以嵌套 Checkbox / Radio 等等
2. 几个容易用到的属性： `label, key, type, mode`







### Popover



#### 基本使用



```js
// 头文件
import { Popover } from 'antd';

// 基本使用——内部可以嵌套其他的元素
const content = (<div></div>);
<Popover content={content} title="Title" trigger="hover">
  <Button>Hover me</Button>
</Popover>

// 通过 visible 控制  popover 的显示
// 需要设置 visible onVisibleChange 两个参数
const [visible, setVisible] = useState(false);
const handleVisibleChange = (newVisible) => {
  	setVisible(newVisible);
};
<Popover visible={visible} onVisibleChange={handleVisibleChange}></Popover>
```



#### API



1. `content`：卡片中显示的内容
2. `Title`：卡片最上方加粗显示的内容
3. `trigger`：['hover' / 'focus' / 'click '] 表示卡片触发显示的动作
4. `placement`：['topRight' / 'top' / 'rightTop'] 总共 12 个方向，表示从哪个方向 pop 出来





### Button



#### 基本使用



```js
import { Button } from 'antd';

<Button>提示内容</Button>
```





#### API



1. type：设置按钮的类型，参见 antd 官网
2. onClick：点击后的回调函数



#### tips



1. onClick 里面不要写 e.target 因为 e.target 不一定是这个按钮，还有可能是按钮上显示的文字





### Input



#### 基本使用



```js


// 调用 input 中的内容: 用 e.target.value
<Input defaultValue={item.name} onChange={(e)=>{setNewItem({...newItem, name: e.target.value});}}</Input>
```





### 弹出对话框 Modal



#### 基本使用



```js
import { Button, Modal } from 'antd';
import { useState } from 'react';

const App = () => {
  const [isModalVisible, setIsModalVisible] = useState(false);

  const showModal = () => {
    setIsModalVisible(true);
  };

  const handleOk = () => {
    setIsModalVisible(false);
  };

  const handleCancel = () => {
    setIsModalVisible(false);
  };

  return (
    <>
      <Button type="primary" onClick={showModal}>
        Open Modal
      </Button>
      <Modal title="Basic Modal" visible={isModalVisible} onOk={handleOk} onCancel={handleCancel}>
        <p>Some contents...</p>
        <p>Some contents...</p>
        <p>Some contents...</p>
      </Modal>
    </>
  );
};

export default App;
```



几个参数：

1. visible：用一个 state hook 记录，在其他地方修改
2. onOk: 点击“确定”按钮的回调函数（**tips:**Ok的k是小写）
3. onCancel：点击“取消”按钮的回调
3. footer: 一个数组，存放在底端的 ReactDOM 元素，（例如：`footer={null}` 表示不要按钮）



tips：

1. modal 需要渲染出来，只是最开始不可见而已





### 表单 Form



#### 基本使用



```js
// 头文件
import { Button, Form, Input, Select } from 'antd';

// 基本使用
<Form>
    <Form.Item>
    	<Input onChange={inputChange}/>
    </Form.Item>
    <Form.Item>
    	<Select />
    </Form.Item>
</Form>

// 在代码中修改表单中的数据
// 使用 form 来强行修改，参考这个博客 https://www.jianshu.com/p/954719e01094
const [form] = Form.useForm();
const inputChange = () => { 
    form.setFieldsValue({...elementBefore, newElement: 'value'});
}
<Form form={form}>
</Form>

// 导出 form 中的数据
// onFinish 函数有一个输入的参数，就是 JSON 格式的表单信息，在 onChange 中处理即可
<Form onFinish={onFinish}>

// 设置表单默认信息
// 不要再底下每个 Form.item 里面设置 defaultValue，在 Form 里设置 InitialValues
<Form initialValues={{
                        'name': item.description,
                        'departments': item.departmentID[0],
                        'date': [moment(item.startTime, dateFormat), moment(item.endTime, dateFormat)],
                        'main_interviewer': item.name,
                        'location': item.location,
                        'note': item.otherInfo
                    }}>
</Form>
``` 





### DatePicker



#### 基本使用



```javascript
// 头文件
import { DatePicker } from 'antd';
const { RangePicker } = DatePicker;

// 设置初始值
// 用到包 moment.js，详见官网文档
import moment from 'moment';
<RangePicker
    defaultValue={[moment('2015/01/01', 'YYYY/MM/DD'), moment('2015/01/01', 'YYYY/MM/DD')]}
	format={dateFormat}
/>
