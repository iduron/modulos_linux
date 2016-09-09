#include <linux/module.h> //se incluye para todo kernel
#include <linux/kernel.h> //se incluye para KERN_INFO
#include <linux/init.h> //se inluye para macros __init y __exit
#include <linux/netfilter.h> //firewalling, NAT y desmenusador de paquetes para linux 
#include <linux/vmalloc.h> //coloca regiones de memoria contigua en espacio de direccion virtual
#include <linux/netfilter_ipv4.h> //demenusador de paquetes tipo IPV4

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ismael Duron");
MODULE_DESCRIPTION("Un modulo simple para registrar trafico de paquetes de red");

static struct nf_hook_ops nfho; //estructura de opciones para hook de filtro de red

unsigned int my_hook(unsigned int hooknum,
	struct sk_buff *skb,
	const struct net_device *in,
	const struct net_device *out,
	int (*okfn)(struct sk_buff *)) {
	struct sock *sk = skb->sk;
	printk("*** Hola paquete *** ");
	return NF_ACCEPT;
}

static int init_filter_if(void)
{
 nfho.hook = my_hook;
 nfho.hooknum = 0;
 nfho.pf = PF_INET;
 nfho.priority = NF_IP_PRI_FIRST;

 nf_register_hook(&nfho);

 return 0;
}

static int __init trafico_inicio(void)
{
 //printk(KERN_INFO "Modulo LOG TRAFICO inicializado!!!\n");
 pr_alert("Modulo LOG TRAFICO inicializado!!!\n");
 init_filter_if();
 return 0; //regresar un valor diff de 0 significa que el modulo no se pudo cargar.
}

static void __exit trafico_fin(void)
{
 //printk(KERN_INFO "Modulo LOG TRAFICO finalizado\n");
 nf_unregister_hook(&nfho);
 pr_alert("Modulo LOG TRAFICO finalizado\n");
}

module_init(trafico_inicio);
module_exit(trafico_fin);
