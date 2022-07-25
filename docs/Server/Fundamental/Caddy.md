[TOC]

## 基本操作

1. `caddy start`：后台运行 caddy

2. `caddy reload` ：重启 *正在运行的* caddy 

3. `/etc/caddy/Caddyfile` ：*Caddyfile* 的位置

## 反向代理

```yaml
starlightxyy.cn {
    reverse_proxy localhost:5120
}
```

## 静态网页

```yaml
note.starlightxyy.cn {
    file_server
    root * /root/apps/mkdocs/site
}
```

**注意！！！** 静态网页根目录不要放在需要 root 权限的地方，否则会 403。

## 检查网络 (curl)

命令：`curl https://note.starlightxyy.cn -v` （`-v`会显示详细信息）

显示：

```shell
root@allenVPS:/etc/caddy## curl https://note.starlightxyy.cn -v
*   Trying 144.34.242.8:443...
* Connected to note.starlightxyy.cn (144.34.242.8) port 443 (##0)
* ALPN, offering h2
* ALPN, offering http/1.1
* successfully set certificate verify locations:
*  CAfile: /etc/ssl/certs/ca-certificates.crt
*  CApath: /etc/ssl/certs
* TLSv1.3 (OUT), TLS handshake, Client hello (1):
* TLSv1.3 (IN), TLS handshake, Server hello (2):
* TLSv1.3 (IN), TLS handshake, Encrypted Extensions (8):
* TLSv1.3 (IN), TLS handshake, Certificate (11):
* TLSv1.3 (IN), TLS handshake, CERT verify (15):
* TLSv1.3 (IN), TLS handshake, Finished (20):
* TLSv1.3 (OUT), TLS change cipher, Change cipher spec (1):
* TLSv1.3 (OUT), TLS handshake, Finished (20):
* SSL connection using TLSv1.3 / TLS_AES_128_GCM_SHA256
* ALPN, server accepted to use h2
* Server certificate:
*  subject: CN=note.starlightxyy.cn
*  start date: Jul 25 00:33:26 2022 GMT
*  expire date: Oct 23 00:33:25 2022 GMT
*  subjectAltName: host "note.starlightxyy.cn" matched cert's "note.starlightxyy.cn"
*  issuer: C=US; O=Let's Encrypt; CN=R3
*  SSL certificate verify ok.
* Using HTTP2, server supports multi-use
* Connection state changed (HTTP/2 confirmed)
* Copying HTTP/2 data in stream buffer to connection buffer after upgrade: len=0
* Using Stream ID: 1 (easy handle 0x55744ae965c0)
> GET / HTTP/2
> Host: note.starlightxyy.cn
> user-agent: curl/7.74.0
> accept: */*
>
* TLSv1.3 (IN), TLS handshake, Newsession Ticket (4):
* Connection state changed (MAX_CONCURRENT_STREAMS == 250)!
< HTTP/2 403
< server: Caddy
< content-length: 0
< date: Mon, 25 Jul 2022 01:45:59 GMT
<
* Connection ##0 to host note.starlightxyy.cn left intact
```

重要信息：

1. `HTTP/2 403` 报错信息

2. `server:Caddy` 可能被其他 web server 占用

3. `connected to ... port 443` 访问的端口
