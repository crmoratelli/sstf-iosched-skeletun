/*
 * SSTF IO Scheduler - Implemented by Carlos Moratelli
 *
 * For Kernel 4.12.4
 * 
 */
#include <linux/blkdev.h>
#include <linux/elevator.h>
#include <linux/bio.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/init.h>

/* SSTF data structure. */
struct sstf_data {
	struct list_head queue;
};

/* Esta função despacha o próximo bloco a ser lido. */
static int sstf_dispatch(struct request_queue *q, int force){
	struct sstf_data *nd = q->elevator->elevator_data;
	char direction = 'R';
	struct request *rq;
	
	/* Aqui deve-se retirar uma requisição da fila e enviá-la para processamento.
	 * Use como exemplo o driver noop-iosched.c. Veja como a requisição é tratada.
	 * 
	 * Antes de retornar da função, imprima o sector que foi atendido.
	 */
	
	printk(KERN_EMERG "[SSTF] dsp %c %lu\n", direction, blk_rq_pos(rq));

	return 1;
}

static void sstf_add_request(struct request_queue *q, struct request *rq){
	struct sstf_data *nd = q->elevator->elevator_data;
	char direction = 'R';

	/* Aqui deve-se adicionar uma requisição na fila do driver.
	 * Use como exemplo o driver noop-iosched.c
	 * 
	 * Antes de retornar da função, imprima o sector que foi adicionado na lista.
	 */
		
	printk(KERN_EMERG "[SSTF] add %c %lu\n", direction, blk_rq_pos(rq));


}


static int sstf_init_queue(struct request_queue *q, struct elevator_type *e){
	struct sstf_data *nd;
	struct elevator_queue *eq;

	/* Implementação da inicialização da fila (queue).
	 * 
	 * Use como exemplo a inicialização da fila no driver noop-iosched.c
	 * 
	 */
	
	return 0;
}

static void sstf_exit_queue(struct elevator_queue *e)
{
	struct sstf_data *nd = e->elevator_data;

	/* Implementação da finalização da fila (queue).
	 * 
	 * Use como exemplo o driver noop-iosched.c
	 * 
	 */

}

/* Infrastrutura dos drivers de IO Scheduling. */
static struct elevator_type elevator_sstf = {
	.ops.sq = {
		.elevator_dispatch_fn		= sstf_dispatch,
		.elevator_add_req_fn		= sstf_add_request,
		.elevator_init_fn		= sstf_init_queue,
		.elevator_exit_fn		= sstf_exit_queue,
	},
	.elevator_name = "sstf",
	.elevator_owner = THIS_MODULE,
};

/* Inicialização do driver. */
static int __init sstf_init(void)
{
	elv_register(&elevator_sstf);

	return 0;
}

/* Finalização do driver. */
static void __exit sstf_exit(void)
{
	elv_unregister(&elevator_sstf);
}

module_init(sstf_init);
module_exit(sstf_exit);


MODULE_AUTHOR("Carlos Moratelli");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SSTF IO scheduler");
