# chatPaper 使用

## 下载

[作者博客](https://zhuanlan.zhihu.com/p/613055271)

## 使用

### openai api

如果长时间得不到结果，多半是 api key 过期了。去 openai 官网上重新申请一个。

### 读取本地论文

```shell
python chat_paper.py --pdf_path "D:\CollegeCourses\信息安全大赛\ERNN_Error-Resilient_RNN_for_Encrypted_Traffic_Detection_towards_Network-Induced_Phenomena.pdf"
```

```shell
python chat_paper.py --pdf_path ".\src\A re-evaluation of intrusion detection accuracy.pdf"
python chat_paper.py --pdf_path ".\src\Certificate-Aware Encrypted Traffic Classification Using Second-Order Markov Chai.pdf"
python chat_paper.py --pdf_path ".\src\MaMPF_ Encrypted Traffic Classification Based on Multi-Attribute Markov Probability Fingerprints.pdf"
python chat_paper.py --pdf_path ".\src\Markov chain fingerprinting to classify encrypted traffic.pdf"
python chat_paper.py --pdf_path ".\src\Robust_smart_phone_app_identification_via_encrypted_network_traffic_analysis.pdf"
```

会读取本地的 pdf 文件，并把结果输出到 `./export` 文件夹下