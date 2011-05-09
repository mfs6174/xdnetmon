void tuichu()
{
  pcap_close(pp);
  guanbixie();
  cout<<"本次运行期间共产生流量"<<fixed<<setprecision(3)<<_mb(gongzuo)<<" 本月流量已用"<<_mb(gongzuo+benyue)<<" 剩余"<<_mb(shezhi.keyong-gongzuo-benyue)<<endl;
  if (shezhi.baocun)
  {
    xiegongzuo(gongzuo);
  }
  exit(0);
}

