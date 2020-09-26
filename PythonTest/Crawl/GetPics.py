#!/usr/bin/env python
# -*- coding: utf-8 -*-
import requests
import re
import pyquery as pq
import json
import time
COOKIE = "SINAGLOBAL=5047529076400.344.1561300290467; UOR=,,login.sina.com.cn; SUBP=0033WrSXqPxfM725Ws9jqgMF55529P9D9W5LM2OkW6xCRSIjfGHLM0L55JpX5KMhUgL.FoeEeh201K.0Sh-2dJLoIEBLxKqLBKzLBKqLxKMLB.qLB.eLxK-L12qL1K2LxK-L1hBLB.qt; ALF=1632623061; SSOLoginState=1601087062; SCF=AoXZH0SXnn7O0HM9TcBOoyrUdzR8qIID4O57TowNnAOvmfqLQVtvDRVltEFazVyrgzdRNEyi_vhA-eOjLC_fQIY.; SUB=_2A25yatYGDeRhGeVM61MS-SfPzzmIHXVRHkDOrDV8PUNbmtAKLXn8kW9NTS-jWkH0M58xJQXO-5ygDA_9Mrv-FZu0; SUHB=0sqBIFiG2If6r4; wvr=6; _s_tentry=login.sina.com.cn; Apache=3887695883646.4204.1601087361763; ULV=1601087362098:35:3:2:3887695883646.4204.1601087361763:1600702648401; wb_view_log_3201399345=2048*11521.25%261536*8651.25; webim_unReadCount=%7B%22time%22%3A1601088423286%2C%22dm_pub_total%22%3A0%2C%22chat_group_client%22%3A0%2C%22chat_group_notice%22%3A0%2C%22allcountNum%22%3A0%2C%22msgbox%22%3A0%7D"

HEADERS = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.108 Safari/537.36',\
        'Cookie': COOKIE
    }

DECODE_DICT = {'%2F': '/', 'mw1024': 'large'}

URLS = []


def download_pic(filePath):
    global URLS
    for url in URLS:
        try:
            content = req.get(url, headers=HEADERS).content
        except Exception as e:
            continue
        filename = url[url.rfind("/") + 1:]
        with open("%s%s" % (filePath, filename), 'wb') as file:
            file.write(content)
        time.sleep(1)
    else:
        URLS = []


def get_url(data_dict):
    q_url = 'https://weibo.com/p/aj/album/loading'
    user_data = data_dict
    for i in range(1, 10000):  #这里是从第一页获取到最后一页
        params = {
            'ajwvr': 6,
            'type': 'photo',
            'owner_uid': int(user_data['owner_uid']),
            'viewer_uid': int(user_data['viewer_uid']),
            'since_id': user_data['since_id'],
            'page_id': int(user_data['page_id']),
            'page': i,
            'ajax_call': 1,
            '__rnd': time.time(),
        }
        try:
            url = requests.get(q_url, headers=HEADERS, params=params)  #刷新下一页
            url = url.json().get('data')
            url = pq.PyQuery(url)
            print("page:%d" % i)
            time.sleep(1)
            url('.ph_ar_box').each(parse_url)
            try:
                user_data['since_id'] = url('.WB_cardwrap').attr('action-data')
                user_data['since_id'] = user_data['since_id'][
                    user_data['since_id'].rfind('since_id=') + 9:]
            except Exception as e:  #最后一页则退出
                return None
        except Exception as e:
            print(e)
            continue


def parse_url(index, tag):
    tmp_url = tag.get('action-data').strip("curclear_picSrc=")  #获取未解码的图片url
    url = tmp_url[:tmp_url.find('.jpg') + 4]
    for key in DECODE_DICT:
        url = url.replace(key, DECODE_DICT[key])  #用初始化时的解码字典进行替换，得到图片真正的url
    URLS.append("http:" + url)  #将图片url存到URLS列表中


def enter_album(html):
    item_dict = {}  #这个字典用来存放下一页的相关信息
    #获取相册第一页的相关信息
    data = re.findall('<script>FM.view\((.*?)\)', html, re.S)  #用正则表达式获取数据
    url = None
    for item in data:
        try:
            item = json.loads(item)  #反序列化
            item = item.get('html')
            html = pq.PyQuery(item)
            keyword = 'photos'
            for tag in html('.tab_link'):
                href = tag.get('href')
                if keyword in href:
                    url = 'https://weibo.com' + href
                    item_dict['page_id'] = re.search('p/(.\d+)/',
                                                     url).group()[2:-1]
                    break
        except Exception as e:
            continue
        if url:
            response = req.get(url, headers=HEADERS)
            htmls = response.content
            data = re.findall('<script>FM.view\((.*?)\)</script>',
                              htmls.decode('utf-8'), re.S)
            for html in data:
                try:
                    html = json.loads(html)
                    html = html.get('html')
                    html = pq.PyQuery(html)
                    next_page = html('.WB_cardwrap').attr('action-data')
                    if next_page:
                        html('.ph_ar_box').each(
                            parse_url)  #获得此页所有含有图片url的标签，并将此标签传到parse_url函数
                        next_page = next_page.split('&')
                        for sub in next_page:
                            sub = sub.split('=')
                            item_dict[sub[0]] = sub[1]
                        get_url(item_dict)
                except Exception as e:
                    continue
            break


def query_user(filePath):
    name = input('>>:').strip()
    text = req.get('https://s.weibo.com/user?q=%s&Refer=weibo_user' % name,
                   headers=HEADERS).text  #查找目标用户
    time.sleep(1)
    html = pq.PyQuery(text)
    for tag in html(".card .info .name"):
        tag = pq.PyQuery(tag)
        if tag.text() == name:
            link = tag.attr('href')
            link = 'https:' + link
            response = req.get(
                link.format(name),
                headers=HEADERS)  #找到标签里用户名与目标用户名一致的标签，获取url,访问该用户
            text = response.text
            enter_album(text)
            time.sleep(1)
            download_pic(filePath)
            break


req = requests.session()


def GetPic(filePath='./data/'):
    query_user(filePath=filePath)


if __name__ == "__main__":
    GetPic()