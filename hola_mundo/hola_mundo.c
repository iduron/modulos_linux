#include <linux/module.h> //se incluye para todo kernel
#include <linux/kernel.h> //se incluye para KERN_INFO
#include <linux/init.h> //se inluye para macros __init y __exit

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ismael Duron");
MODULE_DESCRIPTION("Un modulo simple HOLA MUNDO");

static int __init hola_inicio(void)
{
 //printk(KERN_INFO "Modulo HOLA MUNDO inicializado!!!\n");
 pr_alert("Modulo HOLA MUNDO inicializado!!!\n");
 return 0; //regresar un valor diff de 0 significa que el modulo no se pudo cargar.
}

static void __exit hola_fin(void)
{
 //printk(KERN_INFO "Modulo HOLA MUNDO finalizado\n");
 pr_alert("Modulo HOLA MUNDO finalizado\n");
}

module_init(hola_inicio);
module_exit(hola_fin);
