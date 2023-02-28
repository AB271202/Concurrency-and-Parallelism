#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#define MEM 64000
#include <stdbool.h>

static ucontext_t ctx;
/*
you always want to jump to the context when the execution was inside the conjecture method.
You need not maintain two context variables.

You need to getcontext inside the conjecture method before calling fn and do setcontext when assert fails.
*/
static void conjecture(int len, void *options, int sz, void fn(void *))
{
	// The context returns here!
	
	// The loop below is needed to ensure that the function doesn't go beyond the length of the list!
	static int count;
	count++;
	if (count <= len)
	{
		// printf("Hi");
		char st1[8192];
		/* Prepares ctx. */
		getcontext(&ctx);
		ctx.uc_stack.ss_sp = st1;
		ctx.uc_stack.ss_size = sizeof st1;
		//printf("Hi");
		makecontext(&ctx, (void (*)(void))conjecture, 4,len, options+sz, sz, fn); 

		//printf("Hi\n");
		fn(options);
		//printf("Hi");
		//Doesn't reach below fn(options) 

	}
	// printf("Hi");
	//but will come here after function ends
} // Create context and start traversal

/*
void print_ctx(ucontext_t *ctx) {
	printf("uc_link: %p\n", ctx->uc_link);
	printf("uc_stack.ss_sp: %p, uc_stack.ss_size: %ld, uc_stack.ss_flags: %d\n",
		ctx->uc_stack.ss_sp, ctx->uc_stack.ss_size, ctx->uc_stack.ss_flags);
	print_mctx(ctx->uc_mcontext);
}
void print_mctx(mcontext_t mctx) {
	printf("gregs: ");
	for(int i = 0; i < __NGREG; i++) {
		printf("%llx, ", mctx.__gregs[i]);
	}
	printf("\n");
	printf("fpregs: ");
	printf("%x, %x, %x, %x, %x, %x, %x, %x",
		mctx.__fpregs->__cwd, mctx.__fpregs->__swd,
		mctx.__fpregs->__ftw, mctx.__fpregs->__fop,
		mctx.__fpregs->__rip, mctx.__fpregs->__rdp,
		mctx.__fpregs->__mxcsr, mctx.__fpregs->__mxcr_mask);
	printf("... \n");
}

*/


void assert(bool b)
{
	// printf("assert\n");
	if (b == false)
		setcontext(&ctx);
	

}; // Restore context if condition fails

bool is_prime(int x)
{
	for (int i = 2; i <= x / 2; i++)
	{
		if (x % i == 0)
			return false;
	}
	return true;
}

bool is_lt_40(int x)
{
	return x < 40;
}

int nested(int i)
{
	assert(!is_prime(i));
	return i * i;
}

void app(void *c)
{
	// printf("app\n");
	int *i = (int *)c;
	assert(is_lt_40(*i));
	int x = nested(*i);
	printf("%d\n", x);
}

int main(void)
{
	int mynums[] = {13, 23, 42, 39, 55};
	// The idea is that the execution of fn stops whenever an assertion fails;
	// Failed assert restarts fn with another value from the list.
	// If no assert fails, then the program control just comes back out to main.

	// We have to ensure that conjecture lives in the bottom of the call stack.
	// If the conjecture frame is popped, we will never be able to rollback to it.
	conjecture(5, (void *)mynums, sizeof(int), &app);
	/*
	What is (void*)?
	A void pointer is a pointer that has no associated data type with it.
	A void pointer can hold address of any type and can be typecasted to any type.
	Here it is a int pointer
	We are typecasting the integer pointer to a void*
	*/
}